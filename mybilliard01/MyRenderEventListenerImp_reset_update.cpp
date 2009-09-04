#include "stdafx.h"
#include "my_app.h"


#define MY_FOR_EACH_PHYS_ACTOR( PHYS, ACTOR ) \
    NxActor * ACTOR = ( PHYS->getNumberOfActors() != 0u ) ? ACTOR = PHYS->getActor( 0u ) : NULL; \
    for( size_t i_##ACTOR = 0u; i_##ACTOR < PHYS->getNumberOfActors(); ACTOR = PHYS->getActor( ++(i_##ACTOR) ) )


void MyRenderEventListenerImp::displayReset( RenderBufferFactory * renderFactory, int x, int y, int width, int height )
{
    scene_->setRenderFactory( renderFactory );
    resetDepthMap( renderFactory, width, height );
    resetEffectFeeders( renderFactory );
    resetSharedEffectVariables();
    resetGlobalEffects( renderFactory, width, height );
    resetProjection( (float) width / (float) height );
    resetLightPosition();
}

void MyRenderEventListenerImp::resetDepthMap( RenderBufferFactory * renderFactory, size_t width, size_t height )
{
    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
        cameras_[ i ]->resetRenderTarget( renderFactory, width, height );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        lights_[ i ]->resetRenderTarget( renderFactory, 1024, 1024 );
}

void MyRenderEventListenerImp::resetEffectFeeders( RenderBufferFactory * renderFactory )
{
    const wstring positionOnlyEffectFilename = ConstString::effectFilename_positionOnly();

    MY_FOR_EACH_MODIFY( SceneNodes, iter, sceneNodes_ )
    {
        const wstring nodeName = iter->getNodeName();
        const wstring effectFilename = ConstString::effectFilenameByNodeName( nodeName );

        EffectShaderFeeder * const newFeederComplete
            = createEffectFeeder( iter->getNode(), renderFactory, effectFilename, false );
        iter->setEffectShaderFeeder( NodeHolder::EFFECT_COMPLETE, newFeederComplete );

        EffectShaderFeeder * const newFeederPositionOnly
            = createEffectFeeder( iter->getNode(), renderFactory, positionOnlyEffectFilename, true );
        iter->setEffectShaderFeeder( NodeHolder::EFFECT_CAMERA_0, newFeederPositionOnly );

        EffectShaderFeeder * const newFeederPositionOnly
            = createEffectFeeder( iter->getNode(), renderFactory, positionOnlyEffectFilename, true );
        iter->setEffectShaderFeeder( NodeHolder::EFFECT_LIGHT_0, newFeederPositionOnly );
    }
}

EffectShaderFeeder * MyRenderEventListenerImp::createEffectFeeder( Node * node, RenderBufferFactory * renderFactory, wstring effectFilename, bool bPositionOnly )
{
    const wstring nodeName = node->getName();

    EffectShader * const effect = renderFactory->createEffectShader( effectFilename );
    RETURN_VALUE_UNLESS( effect, NULL );

    EffectShaderFeeder * const newFeeder = new RenderMonkeySemanticFeeder( node, effect, bPositionOnly );
    RETURN_VALUE_UNLESS( newFeeder, NULL );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        wstringstream shadowTexName;
        shadowTexName << L"shadow" << i << L"_Tex";
        if( effect->hasVariableByName( shadowTexName.str() ) )
        {
            ShaderVariable * const shadowTex = effect->createVariableByName( shadowTexName.str() );
            shadowTex->setTexture( lights_[ i ]->getRenderTargetTexture() );
        }

        wstringstream WVP_Name;
        WVP_Name << L"Light" << i << L"_WorldLightProjection";
        if( effect->hasVariableByName( WVP_Name.str() ) )
        {
            ShaderVariable * const WVP = effect->createVariableByName( WVP_Name.str() );
            light_WVP_Variables_[ i ].insert( Light_WVP_Variables::value_type( newFeeder, WVP ) );
        }
    }

    effectFeeders_.push_back( EffectShaderFeederPtr( newFeeder ) );
    return newFeeder;
}

void MyRenderEventListenerImp::resetSharedEffectVariables() 
{
    MY_FOR_EACH_MODIFY( SceneNodes, iter, sceneNodes_ )
    {
        for( size_t i = 0; i < NodeHolder::SIZE_OF_EFFECT_TYPE_ENUM; ++i )
            collectSharedVariables(iter->getEffectShaderFeeder((NodeHolder::EFFECT_TYPE)i)->getEffectShader());
    }

    RenderMonkeySharedSemanticsFeeder * const sharedVaribleFeeder = new RenderMonkeySharedSemanticsFeeder();
    sharedVaribleFeeder_ = SharedEffectVariableFeederPtr( sharedVaribleFeeder );

    MY_FOR_EACH( SharedVariables, iter, sharedVariables_ )
        sharedVaribleFeeder->appendSharedVariable( iter->second );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        wstringstream lightPositionName;
        lightPositionName << L"Light" << i << L"_Position";
        light_Position_sharedVariables_[ i ] = getSharedVariable( lightPositionName.str() );
    }
}

void MyRenderEventListenerImp::collectSharedVariables( EffectShader * effect )
{
    for( size_t i = 0; i < effect->getNumberOfVariables(); ++i )
    {
        EffectShaderVariable * sharedVariable = effect->createEffectVariableByIndex( i );
        if( false == sharedVariable->isShared() ) continue;

        const wstring variableName = sharedVariable->getVariableName();
        sharedVariables_.insert( SharedVariables::value_type( variableName, sharedVariable ) );
    }
}

ShaderVariable * MyRenderEventListenerImp::getSharedVariable( wstring name ) {
    SharedVariables::const_iterator iter = sharedVariables_.find( name );
    return iter->second;
}

void MyRenderEventListenerImp::resetGlobalEffects( RenderBufferFactory * renderFactory, size_t width, size_t height )
{
    blurEffect_ = RenderTargetChainPtr( new RenderTargetChainImp(
        renderFactory, ConstString::effectFilename_Blur(),
        512, 512, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );

    hdrEffect_ = RenderTargetChainPtr( new RenderTargetChainImp(
        renderFactory, ConstString::effectFilename_HDR(),
        width, height, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );

    ssaoEffect_ = RenderTargetChainPtr( new RenderTargetChainImp(
        renderFactory, ConstString::effectFilename_SSAO(),
        width, height, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );
}

void MyRenderEventListenerImp::resetProjection( float aspect )
{
    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
        cameras_[ i ]->setAspect( aspect );

    const RowMajorMatrix44f matProjection = getActiveCamera()->getProjectionMatrix();

    MY_FOR_EACH_MODIFY( SceneNodes, iter, sceneNodes_ )
        iter->getEffectShaderFeeder( NodeHolder::EFFECT_CAMERA_0 )->updateProjection( matProjection );

    sharedVaribleFeeder_->updateProjection( matProjection );
}

void MyRenderEventListenerImp::resetLightPosition()
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i ) 
    {
        MyDepthMapCamera * const light = lights_[ i ];

        float tmp[ 4 ];
        memcpy( tmp, light->getPosition(), sizeof( float ) * 3 );
        tmp[ 3 ] = 1.f;

        light_Position_sharedVariables_[ i ]->setFloatArray( tmp, 4u );
    }
}




void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    updateCamera( elapsedTime );
    updateCameraDistance();
    updateDepthMaps();
    updateEffectVariables( elapsedTime );
    updateStickPower( elapsedTime );
    updateStickPosition();
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime ) {
    getActiveCamera()->update( elapsedTime );
}

void MyRenderEventListenerImp::updateCameraDistance() {
{
    const NxVec3 cameraPosition = getActiveCamera()->getPosition();

    MY_FOR_EACH( SceneNodes, iter, sceneNodes_ )
        iter->updateCameraDistance( cameraPosition );

    sceneNodes_.sort( NodeHolder::sortByDistance() );
}

void MyRenderEventListenerImp::updateDepthMaps()
{
    updateDepthMap( cameras_[ CAMERA_0 ], NodeHolder::EFFECT_COMPLETE );
    updateDepthMap( cameras_[ CAMERA_0 ], NodeHolder::EFFECT_CAMERA_0 );
    updateDepthMap( lights_[ LIGHT_0 ], NodeHolder::EFFECT_LIGHT_0 );
}

void MyRenderEventListenerImp::updateDepthMap( MyDepthMapCamera * depthMap, NodeHolder::EFFECT_TYPE type )
{
    const NxVec3 position = depthMap->getPosition();
    const NxVec3 direction = depthMap->getDirectionVector();
    const RowMajorMatrix44f matrixWorld = depthMap->getViewMatrix();
    const RowMajorMatrix44f matrixView = depthMap->getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = depthMap->getProjectionMatrix() * matrixView;

    MY_FOR_EACH( SceneNodes, iter, sceneNodes_ )
    {
        EffectShaderFeeder * const feeder = iter->getEffectShaderFeeder( type );
        feeder->updateCameraMatrix( position, direction, matrixWorld, matrixView, matrixProjectionView );
    }
}

void MyRenderEventListenerImp::updateEffectVariables( float elapsedTime )
{
    const NxVec3 cameraPosition = getActiveCamera()->getPosition();
    const NxVec3 cameraDirection = getActiveCamera()->getDirectionVector();
    const RowMajorMatrix44f matrixView = getActiveCamera()->getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = getActiveCamera()->getProjectionMatrix() * matrixView;

    sharedVaribleFeeder_->updateCameraMatrix( cameraPosition, cameraDirection, matrixView, matrixProjectionView );


    MY_FOR_EACH_PHYS_ACTOR( phys_, actor )
    {
        RowMajorMatrix44f matrixWorld;
        actor->getGlobalPose().getRowMajor44( matrixWorld );

        NodeHolder * const nodeHolder = (NodeHolder * ) actor->userData;
        EffectShaderFeeder * const feeder = nodeHolder->getEffectShaderFeeder();
        feeder->updateCameraMatrix( cameraPosition, cameraDirection, matrixWorld, matrixView, matrixProjectionView );

        for( size_t j = 0; j < SIZE_OF_LIGHT_ENUM; ++j )
        {
            nodeHolder->getLightVariable( j )
                Light_WVP_Variables::const_iterator iter = light_WVP_Variables_[ j ].find( feeder );
            if( iter == light_WVP_Variables_[ j ].end() ) continue;

            const RowMajorMatrix44f matrixProjectionLightWorld
                = lights_[ j ]->getProjectionViewMatrix() * matrixWorld;
            iter->second->setFloatArray( matrixProjectionLightWorld, 16u );
        }
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

