#pragma once


class RenderableCamera : public CameraMatrixImp, IMPLEMENTS_INTERFACE( RenderTargetCallBack )
{
public: // from RenderTargetCallBack
    virtual void displayOnRenderTargetCallBack( Render * render ) OVERRIDE;

public:
    RenderableCamera( Camera * cameraCollada, bool bRightHand, bool bPositionOnly );

    bool isPositionOnly();

    void setSharedEffectShaderFeeder( EffectShaderFeeder * );
    void appendEffectShaderFeederForActor( EffectShaderFeeder *, NxActor * );

    void setAspect( float aspectRatio ); // for projection

    Camera * getProjectionCamera();

private:
    Camera * const colladaCamera_;
    const bool bPositionOnly_;

    typedef vector< NxActor * > Actors;
    typedef map< EffectShaderFeeder *, Actors > EffectAndActorMap;
    EffectAndActorMap effectAndActorMap_;

    EffectShaderFeeder * sharedVaribleFeeder_;

};

