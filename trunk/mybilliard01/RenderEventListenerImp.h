#pragma once


class RenderEventListenerImp : IMPLEMENTS_INTERFACE( RenderEventListener ), public RenderEffectShader 
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
    RenderEventListenerImp( wstring sceneFile, wstring physX_File );

private: // init
    void initEffect( RenderBufferFactory * renderFactory );
    void connectPhysicsToGraphics();

private: // update
    void updateObjects();

private: // collada
    ScenePtr scene_;
    MyPhysXPtr phys_;

private: // window
    float width_, height_;

private: // camera
    NxActor * camera_;
    float y;

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
        float matWVP_[16];
    };

    typedef list< GeometryUnderEffect > ToRender;
    ToRender toRender_;
    ToRender::const_iterator iter_;
};


