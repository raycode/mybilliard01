#include "Stdafx.h"
#include "my_app.h"


RenderableCamera::RenderableCamera( Camera * cameraCollada, bool bRightHand, bool bPositionOnly )
: CameraMatrixImp( cameraCollada, bRightHand )
, colladaCamera_( cameraCollada )
, bPositionOnly_( bPositionOnly )
{
    deferredClear_ = &RenderableCamera::clear_nothing;
}

void RenderableCamera::displayOnRenderTargetCallBack( Render * render )
{
    (this->*deferredClear_)( render );

    const NxVec3 position = getPosition();
    const NxVec3 direction = getDirectionVector();
    const RowMajorMatrix44f matrixView = getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = getProjectionMatrix() * matrixView;

    vector< const NxVec3 > position_shadowMap;
    vector< const NxVec3 > direction_shadowMap;
    vector< const RowMajorMatrix44f > matrixView_shadowMap;
    vector< const RowMajorMatrix44f > matrixProjectionView_shadowMap;
    
    for( size_t i = 0; i < shadowMapLights_.size(); ++i )
    {
        RenderableCamera * const shadowMap = shadowMapLights_[ i ];

        position_shadowMap.push_back( shadowMap->getPosition() );
        direction_shadowMap.push_back( shadowMap->getDirectionVector() );
        matrixView_shadowMap.push_back( shadowMap->getViewMatrix() );
        matrixProjectionView_shadowMap.push_back( shadowMap->getProjectionMatrix() * *( matrixView_shadowMap.rbegin() ) );
    }

    //---------------

    sharedVaribleFeeder_->updateView_camera( position, direction, matrixView, matrixProjectionView );

    for( size_t i = 0; i < shadowMapLights_.size(); ++i )
    {
        sharedVaribleFeeder_->updateView_shadowMap( i, position_shadowMap[ i ], direction_shadowMap[ i ], matrixView_shadowMap[ i ], matrixProjectionView_shadowMap[ i ] );
    }

    //-----------------

    MY_FOR_EACH( EffectAndActorMap, iterFeeder, effectAndActorMap_ )
    {
        MyEffectShaderFeeder * const feeder = iterFeeder->first;
        feeder->updateView_camera( position, direction, matrixView, matrixProjectionView );

        for( size_t i = 0; i < shadowMapLights_.size(); ++i )
        {
            feeder->updateView_shadowMap( i, position_shadowMap[ i ], direction_shadowMap[ i ], matrixView_shadowMap[ i ], matrixProjectionView_shadowMap[ i ] );
        }

        MY_FOR_EACH( Actors, iterActor, iterFeeder->second )
        {
            NxActor * const actor = *iterActor;
            Node * const node = (Node *) actor->userData;

            //OutputDebugStr( node->getName().c_str() );
            //OutputDebugStr( L"\n" );

            RowMajorMatrix44f matWorld;
            actor->getGlobalPose().getRowMajor44( matWorld );
            feeder->updateModelMatrix( matWorld );

            feeder->displayWithEffect( NodeDisplayerPtr( new NodeDisplayer( node, isPositionOnly() ) ).get() );
        }
    }
}

void RenderableCamera::setSharedEffectShaderFeeder( MyEffectShaderFeeder * sharedVaribleFeeder ) {
    sharedVaribleFeeder_ = sharedVaribleFeeder;
}

void RenderableCamera::setAspect( float aspectRatio ) {
    colladaCamera_->getPerspectiveCamera()->setAspect( aspectRatio );
}

void RenderableCamera::updateProjectionMatrix()
{
    sharedVaribleFeeder_->updateProjection_camera( getProjectionMatrix() );
    for( size_t i = 0; i < shadowMapLights_.size(); ++i )
        sharedVaribleFeeder_->updateProjection_shadowMap( i, shadowMapLights_.at( i )->getProjectionMatrix() );

    MY_FOR_EACH( EffectAndActorMap, iter, effectAndActorMap_ )
    {
        iter->first->updateProjection_camera( getProjectionMatrix() );
        for( size_t i = 0; i < shadowMapLights_.size(); ++i )
            iter->first->updateProjection_shadowMap( i, shadowMapLights_.at( i )->getProjectionMatrix() );
    }
}


void RenderableCamera::appendEffectShaderFeederForActor( MyEffectShaderFeeder * newFeeder, NxActor * actor )
{
    THROW_UNLESS( sharedVaribleFeeder_, exception() );

    EffectAndActorMap::iterator iter = effectAndActorMap_.find( newFeeder );

    if( effectAndActorMap_.end() == iter ) {
        Actors actors;
        actors.push_back( actor );
        effectAndActorMap_.insert( EffectAndActorMap::value_type( newFeeder, actors ) );

    } else {
        iter->second.push_back( actor );
    }

    EffectShader * const effect = newFeeder->getEffectShader();
    sharedVaribleFeeder_->setEffectShader( effect );
}

void RenderableCamera::appendShadowMapLight( RenderableCamera * shadowMapLight ) {
    shadowMapLights_.push_back( shadowMapLight );
}

void RenderableCamera::clearEffectShaderFeeders() {
    effectAndActorMap_.clear();
    sharedVaribleFeeder_ = NULL;
}
void RenderableCamera::clearShadowMapLights() {
    shadowMapLights_.clear();
}


Camera * RenderableCamera::getProjectionCamera() {
    return colladaCamera_;
}


bool RenderableCamera::isPositionOnly() {
    return bPositionOnly_;
}


void RenderableCamera::clear_Color( Render * render ) {
    render->clear_Color( clearColor_ );
}
void RenderableCamera::clear_Z( Render * render ) {
    render->clear_Z( clearZ_ );
}
void RenderableCamera::clear_Stencil( Render * render ) {
    render->clear_Stencil( clearStencil_ );
}
void RenderableCamera::clear_Color_Z( Render * render ) {
    render->clear_Color_Z( clearColor_, clearZ_ );
}
void RenderableCamera::clear_Color_Stencil( Render * render ) {
    render->clear_Color_Stencil( clearColor_, clearStencil_ );
}
void RenderableCamera::clear_Z_Stencil( Render * render ) {
    render->clear_Z_Stencil( clearZ_, clearStencil_ );
}
void RenderableCamera::clear_Color_Z_Stencil( Render * render ) {
    render->clear_Color_Z_Stencil( clearColor_, clearZ_, clearStencil_ );
}
void RenderableCamera::clear_nothing( Render * render ) {
}

void RenderableCamera::clear_Color( NxU32 color ) {
    clearColor_ = color;
    deferredClear_ = &RenderableCamera::clear_Color;
}
void RenderableCamera::clear_Z( float z ) {
    clearZ_ = z;
    deferredClear_ = &RenderableCamera::clear_Z;
}
void RenderableCamera::clear_Stencil( NxU32 stencil ) {
    clearStencil_ = stencil;
    deferredClear_ = &RenderableCamera::clear_Stencil;
}
void RenderableCamera::clear_Color_Z( NxU32 color, float z ) {
    clearColor_ = color;
    clearZ_ = z;
    deferredClear_ = &RenderableCamera::clear_Color_Z;
}
void RenderableCamera::clear_Color_Stencil( NxU32 color, NxU32 stencil ) {
    clearColor_ = color;
    clearStencil_ = stencil;
    deferredClear_ = &RenderableCamera::clear_Color_Stencil;
}
void RenderableCamera::clear_Z_Stencil( float z, NxU32 stencil ) {
    clearZ_ = z;
    clearStencil_ = stencil;
    deferredClear_ = &RenderableCamera::clear_Z_Stencil;
}
void RenderableCamera::clear_Color_Z_Stencil( NxU32 color, float z, NxU32 stencil ) {
    clearColor_ = color;
    clearZ_ = z;
    clearStencil_ = stencil;
    deferredClear_ = &RenderableCamera::clear_Color_Z_Stencil;
}
void RenderableCamera::clear_nothing() {
    deferredClear_ = &RenderableCamera::clear_nothing;
}


