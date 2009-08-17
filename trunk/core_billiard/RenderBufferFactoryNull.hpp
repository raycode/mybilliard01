#pragma once
namespace my_render {


NULL_OBJECT( RenderBufferFactory ) {

    virtual EffectShader * createEffectShader( wstring filename ) OVERRIDE { return NULL; }

    virtual VertexShader * createVertexShader_1_1( wstring filename, wstring entry ) OVERRIDE { return NULL; }
    virtual VertexShader * createVertexShader_2_0( wstring filename, wstring entry ) OVERRIDE { return NULL; }
    virtual VertexShader * createVertexShader_2_0_sw( wstring filename, wstring entry ) OVERRIDE { return NULL; }

    virtual PixelShader * createPixelShader_2_0( wstring filename, wstring entry ) OVERRIDE { return NULL; }
    virtual PixelShader * createPixelShader_2_sw( wstring filename, wstring entry ) OVERRIDE { return NULL; }

    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) OVERRIDE { return NULL; }

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE { return NULL; }
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) OVERRIDE { return NULL; }

    virtual Surface * getBackBuffer( size_t whichBackBuffer ) OVERRIDE { return NULL; }

    virtual Texture * createTexture( wstring filename ) OVERRIDE { return NULL; }

    // destroy
    virtual bool destroyEffectShader( EffectShader *) OVERRIDE { return false; }
    virtual bool destroyVertexShader( VertexShader *) OVERRIDE { return false; }
    virtual bool destroyPixelShader( PixelShader *) OVERRIDE { return false; }
    virtual bool destroyVertexBuffer( VertexBuffer *) OVERRIDE { return false; }
    virtual bool destroyIndexBuffer( IndexBuffer *) OVERRIDE { return false; }
    virtual bool destroySurface( Surface * ) OVERRIDE { return false; }
    virtual bool destroyTexture( Texture * ) OVERRIDE { return false; }

};


}
