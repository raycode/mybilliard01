#pragma once


class CameraMatrixEffect : public CameraMatrixImp, IMPLEMENTS_INTERFACE( RenderTargetCallBack )
{
public: // from RenderTargetCallBack
    virtual void displayOnRenderTargetCallBack( Render * render ) OVERRIDE;

public:
    CameraMatrixEffect( Camera * cameraCollada, bool bRightHand );

    void setSharedEffectShaderFeeder( EffectShaderFeeder * );
    void appendEffectShaderFeederForActor( EffectShaderFeeder *, NxActor * );

    void setAspect( float aspectRatio ); // for projection

private:
    Camera * const colladaCamera_;

    typedef vector< NxActor * > Actors;
    typedef map< EffectShaderFeeder *, Actors > EffectAndActorMap;
    EffectAndActorMap effectAndActorMap_;

    EffectShaderFeeder * sharedVaribleFeeder_;

};

