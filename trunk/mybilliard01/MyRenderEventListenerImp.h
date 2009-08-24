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
    ToRender * createToRender( Node * node, RenderBufferFactory * renderFactory );

    typedef list< ToRenderPtr > ToRenders;
    ToRenders toRenders_;

    ToRenderNull nullToRender_;
};


