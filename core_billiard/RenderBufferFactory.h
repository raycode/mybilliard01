#pragma once
namespace my_render {


INTERFACE_ RenderBufferFactory {
public:
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, float * positions ) = 0; // video memory
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, float * positions ) = 0; // agp memory
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, float * positions ) = 0; // system memory

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, unsigned int * indexies ) = 0;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, unsigned int * indexies ) = 0;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, unsigned int * indexies ) = 0;

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) = 0;

    // Font
    // Sprite
    // Effect
    // Texture

public: // release
    virtual bool releaseVertexBuffer( VertexBuffer *) = 0;
    virtual bool releaseIndexBuffer( IndexBuffer *) = 0;
    virtual bool releaseSurface( Surface * ) = 0;

public: virtual ~RenderBufferFactory() {}
};


}
