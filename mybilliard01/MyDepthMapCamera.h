#pragma once


class MyDepthMapCamera : public CameraMatrixImp, IMPLEMENTS_INTERFACE( RenderTarget )
{
public: // from RenderTarget
    virtual bool displayOnRenderTarget( Render * render, RenderTargetCallBack * ) OVERRIDE;
    virtual Texture * getRenderTargetTexture() OVERRIDE;

public:
    MyDepthMapCamera( float zNear, float zFar, bool bRightHand, NxVec3 pos, NxVec3 dir, NxVec3 up );

    void resetRenderTarget( RenderBufferFactory *, size_t width, size_t height );

private:
    CameraImp * projectionOnlyCamera_;
    const CameraPtr projectionOnlyCameraPtr_;

private:
    RenderTarget * renderTarget_;
};

