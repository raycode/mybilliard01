#include "StdAfx.h"
#include "my_app.h"


ShadowMapLight::ShadowMapLight( float zNear, float zFar, bool bRightHand, NxVec3 pos, NxVec3 dir, NxVec3 up, wstring effectFilename )
: projectionOnlyCamera_( new CameraImp() )
, effectFilename_( effectFilename )
{

    cameraMatrix_ = CameraMatrixPtr( new CameraMatrixImp( projectionOnlyCamera_.get(), bRightHand ) );

    projectionOnlyCamera_->setAsPerspective( true );
    CameraPerspective * const perspective = projectionOnlyCamera_->getPerspectiveCamera();
    perspective->setZNear( zNear );
    perspective->setZFar( zFar );

    cameraMatrix_->setPosition( pos );
    cameraMatrix_->setDirectionVector( dir );
    cameraMatrix_->setUpVector( up );
    cameraMatrix_->setRightVector( dir.cross( up ) );
}

void ShadowMapLight::resetRenderBufferFactory( RenderBufferFactory * renderFactory, const NodeMap * whoDrawShadow )
{
    EffectShader * const effect = renderFactory->createEffectShader( effectFilename_ );
    assert( effect );
    if( NULL == effect ) return;

    ShadowMapEffectShaderFeeder * const feeder =  new ShadowMapEffectShaderFeeder( effect );
    assert( NULL != feeder );

    shadowCallBack_ = MyShadowCallBackPtr( new MyShadowCallBack( feeder, whoDrawShadow ) );
    feeder->addEffectCallBack( shadowCallBack_.get() );

    shadowFeeder_ = GlobalEffectShaderFeederPtr( feeder );

    shadowRenderTarget_ = renderFactory->createRenderTarget( 256, 256 );
    assert( NULL != shadowRenderTarget_ );
}

void ShadowMapLight::updateMatrix()
{
    const RowMajorMatrix44f matrixView = cameraMatrix_->getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = cameraMatrix_->getProjectionMatrix() * matrixView;
    shadowFeeder_->updateMatrix( cameraMatrix_->getPosition(), cameraMatrix_->getDirectionVector(), matrixView, matrixProjectionView );
}

void ShadowMapLight::renderShadowMap( Render * render ) {
    //shadowCallBack_->displayOnRenderTarget( render );
    shadowRenderTarget_->displayOnRenderTarget( render, shadowCallBack_.get() );
}

Texture * ShadowMapLight::getRenderTarget() {
    return shadowRenderTarget_->getTexture();
}

NxVec3 ShadowMapLight::getPosition() {
    return cameraMatrix_->getPosition();
}

RowMajorMatrix44f ShadowMapLight::getProjectionViewMatrix() {
    return cameraMatrix_->getProjectionViewMatrix();
}
