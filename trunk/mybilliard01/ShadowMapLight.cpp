#include "StdAfx.h"
#include "my_app.h"


ShadowMapLight::ShadowMapLight( float zNear, float zFar, bool bRightHand, NxVec3 pos, NxVec3 dir, NxVec3 up, wstring effectFilename )
: CameraMatrixImp( projectionOnlyCamera_ = new CameraImp(), bRightHand )
, effectFilename_( effectFilename )
{
    projectionOnlyCamera_->setAsPerspective( true );
    CameraPerspective * const perspective = projectionOnlyCamera_->getPerspectiveCamera();
    perspective->setZNear( zNear );
    perspective->setZFar( zFar );

    setPosition( pos );
    setDirectionVector( dir );
    setUpVector( up );
    setRightVector( dir.cross( up ) );
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
    const RowMajorMatrix44f matrixView = getViewMatrix();
    const RowMajorMatrix44f matrixProjectionView = getProjectionMatrix() * matrixView;
    shadowFeeder_->updateMatrix( getPosition(), getDirectionVector(), matrixView, matrixProjectionView );
}

void ShadowMapLight::renderShadowMap( Render * render ) {
    shadowCallBack_->drawOnRenderTarget( render );
    //shadowRenderTarget_->drawOnRenderTarget( render, shadowCallBack_.get() );
}

Texture * ShadowMapLight::getRenderTarget() {
    return shadowRenderTarget_->getTexture();
}

