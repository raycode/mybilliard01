#pragma once
namespace my_render {


class NullRenderBufferFactory : IMPLEMENTS_( RenderBufferFactory ) {
public:
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, float * positions ) OVERRIDE { return NULL; }

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned short * indexies ) OVERRIDE { return NULL; }

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned int * indexies ) OVERRIDE { return NULL; }

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) OVERRIDE { return NULL; }
    virtual bool releaseSurface( Surface * ) OVERRIDE { return true; }

    // Font
    // Sprite
    // Effect
    // Texture

};


}
