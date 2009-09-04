#include "stdafx.h"
#include "my_app.h"


void MyRenderEventListenerImp::displayReset( RenderBufferFactory * renderFactory, int x, int y, int width, int height ) {
    resetShadowMap( renderFactory );
    resetEffect( renderFactory );
    scene_->setRenderFactory( renderFactory );
    updateProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory )
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );

        const wstring nodeName = convertString( actor->getName() );
        Node * const node = scene_->getNode( nodeName );

        actor->userData = createEffectFeeder( node, renderFactory );

        if( NULL != node ) nodeMap_.insert( NodeMap::value_type( actor, node ) );
    }

    createSharedVariableFeeder();
    createPostEffects( renderFactory );
}

void MyRenderEventListenerImp::resetShadowMap( RenderBufferFactory * renderFactory ) {
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        shadowMaps_[ i ]->resetRenderBufferFactory( renderFactory, & nodeMap_ );
}

void MyRenderEventListenerImp::updateProjection( float aspect )
{
    getActiveCamera()->setAspect( aspect );

    sharedVaribleFeeder_->updateProjection( getActiveCamera()->getProjectionMatrix() );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
        shadowMaps_[ i ]->updateProjection( aspect );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateProjection( getActiveCamera()->getProjectionMatrix() );
    }
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    getActiveCamera()->update( elapsedTime );
    updateLight();
    updateEffect( elapsedTime );
    updateStickPower( elapsedTime );
    updateStickPosition();
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateLight()
{
    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        shadowMaps_[ i ]->updateMatrix();

        float tmp[ 4 ];
        const NxVec3 position = shadowMaps_[ i ]->getPosition();
        tmp[ 0 ] = position.x;
        tmp[ 1 ] = position.y;
        tmp[ 2 ] = position.z;
        tmp[ 3 ] = 1.f;
        light_Position_Variables_[ i ]->setFloatArray( tmp, 4u );
    }
}

void MyRenderEventListenerImp::updateEffect( float elapsedTime )
{
    const NxVec3 position = getActiveCamera()->getPosition();
    const NxVec3 direction = getActiveCamera()->getDirectionVector();
    const RowMajorMatrix44f matrixView = getActiveCamera()->getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = getActiveCamera()->getProjectionMatrix() * matrixView;

    sharedVaribleFeeder_->updateCameraMatrix( position, direction, matrixView, matrixProjectionView );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );
        RowMajorMatrix44f matrixWorld;
        actor->getGlobalPose().getRowMajor44( matrixWorld );

        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateCameraMatrix( position, direction, matrixWorld, matrixView, matrixProjectionView );

        for( size_t j = 0; j < SIZE_OF_LIGHT_ENUM; ++j )
        {
            Light_WVP_Variables::const_iterator iter = light_WVP_Variables_[ j ].find( feeder );
            if( iter == light_WVP_Variables_[ j ].end() ) continue;

            const RowMajorMatrix44f matrixProjectionLightWorld
                = shadowMaps_[ j ]->getProjectionViewMatrix() * matrixWorld;
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

EffectShaderFeeder * MyRenderEventListenerImp::createEffectFeeder( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstString::effectFilenameByNodeName( nodeName );
    EffectShader * const effect = renderFactory->createEffectShader( effectFilename );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    EffectShaderFeederPtr newFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( node, effect ) );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        wstringstream shadowTexName;
        shadowTexName << L"shadow" << i << L"_Tex";
        if( effect->hasVariableByName( shadowTexName.str() ) )
            effect->createVariableByName( shadowTexName.str() )
                ->setTexture( shadowMaps_[ i ]->getRenderTarget() );

        wstringstream WVP_Name;
        WVP_Name << L"Light" << i << L"_WorldLightProjection";
        if( effect->hasVariableByName( WVP_Name.str() ) )
            light_WVP_Variables_[ i ].insert(
                Light_WVP_Variables::value_type( newFeeder.get(),
                    effect->createVariableByName( WVP_Name.str() )
                )
            );
    }

    findSharedVariables( effect );

    feeders_.push_back( newFeeder );

    return newFeeder.get();
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
    if( sharedVariables_.end() == iter ) return & nullShaderVariable_;
    return iter->second;
}

void MyRenderEventListenerImp::createSharedVariableFeeder() 
{
    RenderMonkeySharedSemanticsFeeder * const sharedVaribleFeeder = new RenderMonkeySharedSemanticsFeeder();
    sharedVaribleFeeder_ = GlobalEffectShaderFeederPtr( sharedVaribleFeeder );

    MY_FOR_EACH( SharedVariables, iter, sharedVariables_ )
        sharedVaribleFeeder->appendSharedVariable( iter->second );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i )
    {
        wstringstream positionName;
        positionName << L"Light" << i << L"_Position";
        light_Position_Variables_[ i ] = getSharedVariable( positionName.str() );
    }
}

void MyRenderEventListenerImp::createPostEffects( RenderBufferFactory * renderFactory )
{
    blurEffect_ = RenderTargetChainPtr( new PostEffectImp( renderFactory, ConstString::effectFilename_Blur(),
        512, 512, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );

    hdrEffect_ = RenderTargetChainPtr( new PostEffectImp( renderFactory, ConstString::effectFilename_HDR(),
        1024, 1024, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );

    ssaoEffect_ = RenderTargetChainPtr( new PostEffectImp( renderFactory, ConstString::effectFilename_SSAO(),
        1024, 1024, L"outputWidthInverse", L"outputHeightInverse",
        L"inputTexture_Tex", L"inputWidthInverse", L"inputHeightInverse" ) );
}

