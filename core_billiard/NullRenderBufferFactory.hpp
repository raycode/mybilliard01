#pragma once
namespace my_render {


class NullRenderBufferFactory : IMPLEMENTS_( RenderBufferFactory ) {
public:
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

public: // release
    virtual bool releaseEffectShader( EffectShader *) OVERRIDE { return false; }
    virtual bool releaseVertexShader( VertexShader *) OVERRIDE { return false; }
    virtual bool releasePixelShader( PixelShader *) OVERRIDE { return false; }
    virtual bool releaseVertexBuffer( VertexBuffer *) OVERRIDE { return false; }
    virtual bool releaseIndexBuffer( IndexBuffer *) OVERRIDE { return false; }
    virtual bool releaseSurface( Surface * ) OVERRIDE { return false; }
    virtual bool releaseTexture( Texture * ) OVERRIDE { return false; }

};


}
