#pragma once


class MyRenderEventListenerImp : IMPLEMENTS_INTERFACE( RenderEventListener ), public RenderEffectShader 
{
public: // from RenderEventListener
    virtual void init( RenderBufferFactory * ) OVERRIDE;
    virtual void displayReset( int x, int y, int width, int height ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE;
    virtual void display( Render * ) OVERRIDE;
    virtual void display( Render * render, size_t pass ) OVERRIDE;
    virtual void displayLost() OVERRIDE;
    virtual void destroy() OVERRIDE;

public:
    MyRenderEventListenerImp( wstring sceneFile, wstring physX_File );

    MyCamera * getMyCamera();

private: // init
    void initEffect( RenderBufferFactory * renderFactory );
    void connectPhysicsToGraphics();

private: // update
    void updateCamera( float elapsedTime );
    void updateObjects( float elapsedTime );

private: // collada
    ScenePtr scene_;
    MyPhysXPtr phys_;

private: // camera
    MyCameraPtr camera_;
    RowMajorMatrix44f matrixProjection_;
    RowMajorMatrix44f matrixProjectionView_;
    bool bRightHandHardware_;

    void updateCameraProjection( float aspectRatio );
    void updateCameraView();

private: // effect
    EffectShader * effect_;
    ShaderVariable * tech_, * wvp_, * world_;

private: // render effect

    struct GeometryUnderEffect {
        GeometryUnderEffect( Node * node )
            : node_( node )
        {}

        Node * node_;
        float matWorld_[16];
        float matWorldViewProjection_[16];
    };

    typedef list< GeometryUnderEffect > ToRender;
    ToRender toRenders_;
    ToRender::const_iterator iter_;
};


