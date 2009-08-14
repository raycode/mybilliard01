#pragma once
namespace my_render {


class NullRenderBufferFactory : IMPLEMENTS_( RenderBufferFactory ) {
public:
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) OVERRIDE { return NULL; }

    // Font
    // Sprite
    // Effect
    // Texture

public: // release
    virtual bool releaseVertexBuffer( VertexBuffer *) OVERRIDE { return true; }
    virtual bool releaseIndexBuffer( IndexBuffer *) OVERRIDE { return true; }
    virtual bool releaseSurface( Surface * ) OVERRIDE { return true; }

};


}
