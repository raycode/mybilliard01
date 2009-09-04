#include "StdAfx.h"
#include "my_app.h"


MyDepthMapCamera::MyDepthMapCamera( float zNear, float zFar, bool bRightHand, NxVec3 pos, NxVec3 dir, NxVec3 up )
: CameraMatrixImp( projectionOnlyCamera_ = new CameraImp(), bRightHand )
, projectionOnlyCameraPtr_( projectionOnlyCamera_ )
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

void MyDepthMapCamera::resetRenderTarget( RenderBufferFactory * renderFactory, size_t width, size_t height )
{
    renderTarget_ = renderFactory->createRenderTarget( width, height );
    THROW_UNLESS( renderTarget_, exception() );
}

bool RenderTargetChainImp::displayOnRenderTarget( Render * render, RenderTargetCallBack * callBack ) {
    return renderTarget_->displayOnRenderTarget( render, callBack );
}

Texture * MyDepthMapCamera::getRenderTargetTexture() {
    return renderTarget_->getRenderTargetTexture();
}


