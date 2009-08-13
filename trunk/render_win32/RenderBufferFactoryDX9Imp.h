#pragma once
namespace my_render_win32_dx9_imp {


class RenderBufferFactoryDX9Imp : IMPLEMENTS_( RenderBufferFactoryDX9 ) {
public: // from RenderBufferFactory
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, float * positions ) OVERRIDE;
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, float * positions ) OVERRIDE;

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE;

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE;

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) OVERRIDE;
    virtual bool releaseSurface( Surface * ) OVERRIDE;

public: // from RenderEventListener
    virtual void init( RenderBufferFactory * ) OVERRIDE;
    virtual void displayReset( RenderBufferFactory *, int x, int y, int width, int height ) OVERRIDE;
    virtual void displayLost( RenderBufferFactory * ) OVERRIDE;
    virtual void destroy( RenderBufferFactory * ) OVERRIDE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE {}
    virtual void display( Render * ) OVERRIDE {}

public:
    RenderBufferFactoryDX9Imp( IDirect3DDevice9 * d3dDevice );

private:
    IDirect3DDevice9 * getD3D9();

private:
    IDirect3DDevice9 * const d3dDevice_;

private:
    typedef list< VertexBufferPtr > StaticVertexies;
    StaticVertexies staticVertexies_;

    typedef list< VertexBufferPtr > DynamicVertexies;
    DynamicVertexies dynamicVertexies_;

    typedef list< VertexBufferPtr > StreamVertexies;
    StreamVertexies streamVertexies_;

    typedef list< IndexBufferPtr > StaticIndexies;
    StaticIndexies staticIndexies_;

    typedef list< IndexBufferPtr > DynamicIndexies;
    DynamicIndexies dynamicIndexies_;

    typedef list< IndexBufferPtr > StreamIndexies;
    StreamIndexies streamIndexies_;

    typedef list< SurfaceDX9ImpPtr > Surfaces;
    Surfaces surfaces_;

};


}
