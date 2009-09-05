#include "Stdafx.h"
#include "my_app.h"


CameraRenderTarget::CameraRenderTarget( Camera * cameraCollada, bool bRightHand )
: CameraMatrixImp( cameraCollada, bRightHand )
, colladaCamera_( cameraCollada )
{
}

void CameraRenderTarget::displayOnRenderTargetCallBack( Render * render )
{
    const NxVec3 position = getPosition();
    const NxVec3 direction = getDirectionVector();
    const RowMajorMatrix44f matrixView = getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = getProjectionMatrix() * matrixView;

    sharedVaribleFeeder_->updateCameraMatrix( position, direction, matrixView, matrixProjectionView );


    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setClockWise();

    MY_FOR_EACH( EffectAndActorMap, iterFeeder, effectAndActorMap_ )
    {
        EffectShaderFeeder * const feeder = iterFeeder->first;
        feeder->updateCameraMatrix( position, direction, matrixView, matrixProjectionView );

        MY_FOR_EACH( Actors, iterActor, iterFeeder->second )
        {
            NxActor * const actor = *iterActor;
            Node * const node = (Node *) actor->userData;

            RowMajorMatrix44f matWorld;
            actor->getGlobalPose().getRowMajor44( matWorld );
            feeder->updateModelMatrix( matWorld );

            feeder->displayWithEffect( NodeDisplayerPtr( new NodeDisplayer( node, false ) ).get() );
        }
    }
}

void CameraRenderTarget::setSharedEffectShaderFeeder( EffectShaderFeeder * sharedVaribleFeeder ) {
    sharedVaribleFeeder_ = sharedVaribleFeeder;
}

void CameraRenderTarget::setAspect( float aspectRatio )
{
    colladaCamera_->getPerspectiveCamera()->setAspect( aspectRatio );
    
    MY_FOR_EACH( EffectAndActorMap, feeder, effectAndActorMap_ )
        feeder->first->updateCameraProjection( getProjectionMatrix() );
}


void CameraRenderTarget::appendEffectShaderFeederForActor( EffectShaderFeeder * newFeeder, NxActor * actor )
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



