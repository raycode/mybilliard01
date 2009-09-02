#pragma once


class ShadowMapLight
    : public CameraMatrixImp
    , IMPLEMENTS_INTERFACE( CameraMatrix )
{
public:
    typedef map< NxActor *, Node * > NodeMap;

    void resetRenderBufferFactory( RenderBufferFactory *, const NodeMap * whoDrawShadow );

    void updateProjection( float aspect ) {}

    void updateMatrix();

    void renderShadowMap( Render * render );

    Texture * getRenderTarget();

public:
    ShadowMapLight( float zNear, float zFar, bool bRightHand, NxVec3 pos, NxVec3 dir, NxVec3 up, wstring effectFilename );

private:
    CameraImp * projectionOnlyCamera_;
    wstring effectFilename_;

private:
    RenderTarget * shadowRenderTarget_;
    GlobalEffectShaderFeederPtr shadowFeeder_;
    MyShadowCallBackPtr shadowCallBack_;
};

