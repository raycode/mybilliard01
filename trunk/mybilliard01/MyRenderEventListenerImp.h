#pragma once


class MyRenderEventListenerImp
    : IMPLEMENTS_INTERFACE( RenderEventListener )
{
public: // from RenderEventListener
    virtual void init( RenderBufferFactory * ) OVERRIDE;
    virtual void displayReset( int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE;
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public:
    MyRenderEventListenerImp( wstring sceneFile, wstring physX_File );

    MyCamera * getMyCamera();

private: // init
    void initCamera( NxVec3 pos, NxVec3 dir );
    void initEffect( RenderBufferFactory * renderFactory );
    void initEffectLights();

private: // update
    void updateCamera( float elapsedTime );
    void updateCameraProjection( float aspectRatio );
    void updateCameraView();
    void updateCameraPosAndDir();
    void updateEffect( float elapsedTime );

private:
    ScenePtr scene_;
    MyPhysXPtr phys_;

private: // camera
    MyCameraPtr camera_;
    RowMajorMatrix44f matrixView_;
    RowMajorMatrix44f matrixProjection_;
    RowMajorMatrix44f matrixProjectionView_;
    NxVec3 cameraPos_, cameraDir_;
    const bool bRightHandHardware_;

private: // effect
    EffectShaderFeeder * createToRender( Node * node, RenderBufferFactory * renderFactory );
    void findSharedVariables( EffectShader * effect);
    ShaderVariable * getSharedVariable( wstring name );

    typedef list< EffectShaderFeederPtr > EffectShaderFeeders;
    EffectShaderFeeders feeders_;

    EffectShaderFeederNull nullToRender_;

    typedef map< wstring, ShaderVariablePtr > SharedVariables;
    SharedVariables sharedVariables_;

};


