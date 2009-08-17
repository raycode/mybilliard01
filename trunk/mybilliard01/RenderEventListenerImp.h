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
    RenderEventListenerImp();

public: // DXUT
    CModelViewerCamera          camera_;               // A model viewing camera

private:
    EffectShader * effect_;
    ShaderVariable * tech_, * wvp_, * world_, * time_;
    VertexBuffer * vb_;

private: // Collada scene object
    ScenePtr scene_;
};


