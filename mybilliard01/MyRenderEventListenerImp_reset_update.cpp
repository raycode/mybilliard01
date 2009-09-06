#include "stdafx.h"
#include "my_app.h"


void MyRenderEventListenerImp::displayReset( RenderBufferFactory * renderFactory, int x, int y, int width, int height )
{
    scene_->setRenderFactory( renderFactory );
    resetEffect( renderFactory, width, height );
    resetShadowMap();
    updateProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory, size_t width, size_t height )
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        resetEffect( renderFactory, lights_[ i ], ConstString::effectFilename_shadowMap( i + 1 ) );
        lightRenderTargets_[ i ] = renderFactory->createRenderTarget( 1024, 1024 );
    }

    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
    {
        resetEffect( renderFactory, cameras_[ i ], L"" );
        resetEffect( renderFactory, depthCameras_[ i ], ConstString::effectFilename_depthCull() );
    }
}

void MyRenderEventListenerImp::resetShadowMap()
{
    MY_FOR_EACH( EffectShaderFeeders, iterFeeder, feeders_ )
    {
        EffectShaderFeeder * const feeder = iterFeeder->get();
        EffectShader * const effect = feeder->getEffectShader();

        for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        {
            wstringstream variableName;
            variableName << L"shadow" << i << L"_Tex";
            if( false == effect->hasVariableByName( variableName.str() ) ) continue;
            ShaderVariable * const shadowMapVariable = effect->createVariableByName( variableName.str() );

            Texture * const shadowMapTexture = lightRenderTargets_[ i ]->getRenderTargetTexture();
            shadowMapVariable->setTexture( shadowMapTexture );
        }
    }
}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory, RenderableCamera * camera, wstring effectFilenameForPositionOnly )
{
    EffectShaderFeederPtr sharedFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( true ) );
    sharedFeeders_.push_back( sharedFeeder );

    camera->setSharedEffectShaderFeeder( sharedFeeder.get() );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );

        const wstring nodeName = convertString( actor->getName() );
        Node * const node = scene_->getNode( nodeName );
        if( NULL == node ) continue;
        actor->userData = node;

        const wstring effectFilename = camera->isPositionOnly()
            ? effectFilenameForPositionOnly : ConstString::effectFilenameByNodeName( nodeName );
        EffectShaderFeeder * const newFeeder = createEffectFeeder( effectFilename, renderFactory );
        camera->appendEffectShaderFeederForActor( newFeeder, actor );

        sharedFeeder->setEffectShader( newFeeder->getEffectShader() );
    }
}

EffectShaderFeeder * MyRenderEventListenerImp::createEffectFeeder( wstring effectFilename, RenderBufferFactory * renderFactory )
{
    EffectShader * const newEffect = renderFactory->createEffectShader( effectFilename );
    RETURN_VALUE_UNLESS( newEffect, NULL );

    MY_FOR_EACH( EffectShaderFeeders, feeder, feeders_ )
        if( (*feeder)->getEffectShader() == newEffect ) return feeder->get();

    EffectShaderFeederPtr newFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( false ) );
    feeders_.push_back( newFeeder );
    findSharedVariables( newEffect );
    newFeeder->setEffectShader( newEffect );
    return newFeeder.get();
}

void MyRenderEventListenerImp::updateProjection( float aspect )
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        lights_[ i ]->updateCameraProjection();

    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
    {
        cameras_[ i ]->setAspect( aspect );
        depthCameras_[ i ]->setAspect( aspect );

        cameras_[ i ]->updateCameraProjection();
        depthCameras_[ i ]->updateCameraProjection();
    }
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    updateCamera( elapsedTime );
    updateStickPower( elapsedTime );
    updateStickPosition();
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime )
{
    //for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
    size_t i = activeCamera_;
    {
        MyCamera * const camera = cameras_[ i ];
        RenderableCamera * const depthCamera = depthCameras_[ i ];
        camera->update( elapsedTime );

        depthCamera->setPosition( camera->getPosition() );
        depthCamera->setUpVector( camera->getUpVector() );
        depthCamera->setDirectionVector( camera->getDirectionVector() );
        depthCamera->setRightVector( camera->getRightVector() );
    }
}

void MyRenderEventListenerImp::updateStickPosition() {
    //const NxExtendedVec3 cameraPos = getActiveCamera()->getPosition();
    //NxVec3 newStickPosition( (NxReal) cameraPos.x, (NxReal) cameraPos.y, (NxReal) cameraPos.z );
    //newStickPosition += getActiveCamera()->getRightVector() * 10.f;
    //getStick()->moveGlobalPosition( newStickPosition );

    //NxVec3 right = getActiveCamera()->getRightVector();
    //NxVec3 up = getActiveCamera()->getUpVector();
    //NxVec3 dir = getActiveCamera()->getDirectionVector();
    //getStick()->moveGlobalOrientation( NxMat33( right, up, dir ) );
}

void MyRenderEventListenerImp::updateStickPower( float elapsedTime ) {
    if( bChargingStickPower_ ) chargedStickPower_ = std::min( elapsedTime + chargedStickPower_, 100.f );
}

SoundHandle * MyRenderEventListenerImp::getRandomSound( int soundType )
{
    uniform_int<int> unif( 0, sounds_[ soundType ].size() -1 );
    const size_t index = unif( randomEngine );
    return sounds_[ soundType ].at( index ).get();
}

void MyRenderEventListenerImp::findSharedVariables( EffectShader * effect ) {

    const size_t nVariables = effect->getNumberOfVariables();

    for( size_t i = 0; i < nVariables; ++i )
    {
        EffectShaderVariable * sharedVariable = effect->createEffectVariableByIndex( i );
        if( false == sharedVariable->isShared() ) continue;

        const wstring variableName = sharedVariable->getVariableName();
        if( sharedVariables_.find( variableName ) != sharedVariables_.end() ) continue;

        sharedVariables_.insert( SharedVariables::value_type( variableName, sharedVariable ) );
    }
}

ShaderVariable * MyRenderEventListenerImp::getSharedVariable( wstring name ) {
    SharedVariables::const_iterator iter = sharedVariables_.find( name );
    RETURN_VALUE_UNLESS( sharedVariables_.end() != iter, NULL );
    return iter->second;
}
