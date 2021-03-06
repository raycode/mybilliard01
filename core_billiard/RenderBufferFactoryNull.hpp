#pragma once
namespace my_render {


NULL_OBJECT( RenderBufferFactory ) {

    virtual EffectShader * createEffectShader( wstring filename ) OVERRIDE { return NULL; }

    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }

    virtual Texture * createTexture( wstring filename ) OVERRIDE { return NULL; }
    virtual RenderTarget * createRenderTarget( size_t width, size_t height ) OVERRIDE { return NULL; }

    // destroy
    virtual bool destroyEffectShader( EffectShader *) OVERRIDE { return false; }
    virtual bool destroyVertexBuffer( VertexBuffer *) OVERRIDE { return false; }
    virtual bool destroyTexture( Texture * ) OVERRIDE { return false; }
    virtual bool destroyRenderTarget( RenderTarget * ) OVERRIDE { return false; }

};


}
