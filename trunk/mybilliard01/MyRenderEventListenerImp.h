#pragma once


class MyRenderEventListenerImp
    : IMPLEMENTS_INTERFACE( RenderEventListener )
{
public: // from RenderEventListener
    virtual void init() OVERRIDE;
    virtual void displayReset( RenderBufferFactory *, int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE;
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public:
    MyRenderEventListenerImp( wstring sceneFile, wstring physX_File );

public:
    MyCamera * getMyCamera();
    NxVec3 getBallPosition();
    void shotCueBall();
    void bringCueBallBack();

private:
    NxActor * getCueBall();
    NxActor * getStick();

private: // init
    void initCamera( NxVec3 pos, NxVec3 dir );
    void initPhysObjects();
    void initEffect( RenderBufferFactory * renderFactory );
    void initEffectLights();

private: // update
    void updateCamera( float elapsedTime );
    void updateCameraProjection( float aspectRatio );
    void updateEffectProjection();
    void updateCameraView();
    void updateCameraPosAndDir();
    void updateEffect( float elapsedTime );
    void updateStickPosition();

private:
    ScenePtr scene_;
    MyPhysXPtr phys_;

private: // physx
    enum { ACTOR_CUE_BALL, ACTOR_STICK, SIZE_OF_ACTORS };
    NxActor * actors_[ SIZE_OF_ACTORS ];

    BallContactReport ballContactReport_;

private: // camera
    MyCameraPtr camera_;
    RowMajorMatrix44f matrixView_;
    RowMajorMatrix44f matrixProjection_;
    RowMajorMatrix44f matrixProjectionView_;
    NxVec3 cameraPos_, cameraDir_;
    const bool bRightHandHardware_;

private: // keyboard input
    NxVec3 defaultCueBallPos_;

private: // effect
    EffectShaderFeeder * createEffectFeeder( Node * node, RenderBufferFactory * renderFactory );
    void createSharedVariableFeeder();
    void findSharedVariables( EffectShader * effect);
    ShaderVariable * getSharedVariable( wstring name );

    typedef list< EffectShaderFeederPtr > EffectShaderFeeders;
    EffectShaderFeeders feeders_;
    EffectShaderFeederPtr sharedVaribleFeeder_;

    EffectShaderFeederNull nullToRender_;
    ShaderVariableNull nullShaderVariable_;

    typedef map< wstring, ShaderVariablePtr > SharedVariables;
    SharedVariables sharedVariables_;

};


