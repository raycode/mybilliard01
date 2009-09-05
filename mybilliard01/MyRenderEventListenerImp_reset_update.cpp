#include "stdafx.h"
#include "my_app.h"


void MyRenderEventListenerImp::displayReset( RenderBufferFactory * renderFactory, int x, int y, int width, int height )
{
    resetEffect( renderFactory, width, height );
    scene_->setRenderFactory( renderFactory );
    updateProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory, size_t width, size_t height )
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        resetEffect( renderFactory, lights_[ i ] );
        lightRenderTargets_[ i ] = renderFactory->createRenderTarget( 1024, 1024 );
    }

    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
    {
        resetEffect( renderFactory, cameras_[ i ] );
        resetEffect( renderFactory, depthCameras_[ i ] );
        depthCameraRenderTargets_[ i ] = renderFactory->createRenderTarget( width, height );
    }

    MY_FOR_EACH( EffectShaderFeeders, iterFeeder, feeders_ )
    {
        EffectShaderFeeder * const feeder = iterFeeder->get();
        EffectShader * const effect = feeder->getEffectShader();

        for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        {
            wstringstream variableName;
            variableName << L"shadow" << i << L"_Tex";
            if( false == effect->hasVariableByName( variableName.str() ) ) continue;

            Texture * const shadowMapTexture = lightRenderTargets_[ i ]->getRenderTargetTexture();
            ShaderVariable * const shadowMapVariable = effect->createVariableByName( variableName.str() );
            shadowMapVariable->setTexture( shadowMapTexture );
        }
    }

}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory, RenderableCamera * camera )
{
    EffectShaderFeederPtr sharedFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( true ) );
    sharedFeeders_.push_back( sharedFeeder );

    camera->setSharedEffectShaderFeeder( sharedFeeder.get() );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );

        const wstring nodeName = convertString( actor->getName() );
        Node * const node = scene_->getNode( nodeName );
        if( NULL == node ) continue;
        actor->userData = node;

        if( camera->isPositionOnly() ) {
            const wstring effectFilename2 = ConstString::effectFilename_positionOnly();
            EffectShaderFeeder * const newFeeder2 = createEffectFeeder( effectFilename2, renderFactory );
            camera->appendEffectShaderFeederForActor( newFeeder2, actor );

        } else {
            const wstring effectFilename1 = ConstString::effectFilenameByNodeName( nodeName );
            EffectShaderFeeder * const newFeeder1 = createEffectFeeder( effectFilename1, renderFactory );
            camera->appendEffectShaderFeederForActor( newFeeder1, actor );
        }
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
    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
    {
        cameras_[ i ]->setAspect( aspect );
        depthCameras_[ i ]->setAspect( aspect );
    }
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    updateCamera( elapsedTime );
    updateSharedVariables();
    updateStickPower( elapsedTime );
    updateStickPosition();
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime )
{
    MyCamera * const camera = getActiveCamera();
    camera->update( elapsedTime );
    depthCameras_[ 0 ]->setPosition( camera->getPosition() );
    depthCameras_[ 0 ]->setUpVector( camera->getUpVector() );
    depthCameras_[ 0 ]->setDirectionVector( camera->getDirectionVector() );
    depthCameras_[ 0 ]->setRightVector( camera->getRightVector() );
}

void MyRenderEventListenerImp::updateSharedVariables()
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        const NxVec3 position = lights_[ i ]->getPosition();

        float tmp[ 4 ];
        memcpy( tmp, position.get(), sizeof( float ) * 3 );
        tmp[ 3 ] = 1.f;

        wstringstream variableName;
        variableName << "Light" << i << "_Position";
        getSharedVariable( variableName.str() )->setFloatArray( tmp, 4u );
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
