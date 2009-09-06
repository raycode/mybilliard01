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

    sharedVaribleFeeder_->updateView_camera( position, direction, matrixView, matrixProjectionView );

    MY_FOR_EACH( EffectAndActorMap, iterFeeder, effectAndActorMap_ )
    {
        MyEffectShaderFeeder * const feeder = iterFeeder->first;
        feeder->updateView_camera( position, direction, matrixView, matrixProjectionView );

        MY_FOR_EACH( Actors, iterActor, iterFeeder->second )
        {
            NxActor * const actor = *iterActor;
            Node * const node = (Node *) actor->userData;

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

void RenderableCamera::updateCameraProjection()
{
    sharedVaribleFeeder_->updateProjection_camera( getProjectionMatrix() );

    MY_FOR_EACH( EffectAndActorMap, feeder, effectAndActorMap_ )
        feeder->first->updateProjection_camera( getProjectionMatrix() );
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


