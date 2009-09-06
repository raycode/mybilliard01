#pragma once


class RenderableCamera : public CameraMatrixImp, IMPLEMENTS_INTERFACE( RenderTargetCallBack )
{
public: // from RenderTargetCallBack
    virtual void displayOnRenderTargetCallBack( Render * render ) OVERRIDE;

public:
    virtual void clear_Color( NxU32 color );
    virtual void clear_Z( float z );
    virtual void clear_Stencil( NxU32 stencil );
    virtual void clear_Color_Z( NxU32 color, float z );
    virtual void clear_Color_Stencil( NxU32 color, NxU32 stencil );
    virtual void clear_Z_Stencil( float z, NxU32 stencil );
    virtual void clear_Color_Z_Stencil( NxU32 color, float z, NxU32 stencil );
    virtual void clear_nothing();

public:
    RenderableCamera( Camera * cameraCollada, bool bRightHand, bool bPositionOnly );

    bool isPositionOnly();

    void setSharedEffectShaderFeeder( EffectShaderFeeder * );
    void appendEffectShaderFeederForActor( EffectShaderFeeder *, NxActor * );

    void setAspect( float aspectRatio ); // for projection
    void updateCameraProjection();

    Camera * getProjectionCamera();

private:
    Camera * const colladaCamera_;
    const bool bPositionOnly_;

    typedef vector< NxActor * > Actors;
    typedef map< EffectShaderFeeder *, Actors > EffectAndActorMap;
    EffectAndActorMap effectAndActorMap_;

    EffectShaderFeeder * sharedVaribleFeeder_;

private:
    NxU32 clearColor_, clearStencil_;
    float clearZ_;

    void clear_Color( Render * );
    void clear_Z( Render * );
    void clear_Stencil( Render * );
    void clear_Color_Z( Render * );
    void clear_Color_Stencil( Render * );
    void clear_Z_Stencil( Render * );
    void clear_Color_Z_Stencil( Render * );
    void clear_nothing( Render * );

    typedef void (RenderableCamera::*DeferredClear)( Render * );
    DeferredClear deferredClear_;

};

