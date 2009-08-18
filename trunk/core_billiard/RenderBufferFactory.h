#pragma once
namespace my_render {


MY_INTERFACE RenderBufferFactory {
    virtual ~RenderBufferFactory() {}

    // shader
    virtual EffectShader * createEffectShader( wstring filename ) PURE;

    virtual VertexShader * createVertexShader_1_1( wstring filename, wstring entry ) PURE;
    virtual VertexShader * createVertexShader_2_0( wstring filename, wstring entry ) PURE;
    virtual VertexShader * createVertexShader_2_0_sw( wstring filename, wstring entry ) PURE;

    virtual PixelShader * createPixelShader_2_0( wstring filename, wstring entry ) PURE;
    virtual PixelShader * createPixelShader_2_sw( wstring filename, wstring entry ) PURE;

    // vertex buffer, index buffer
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) PURE; // video memory
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) PURE; // agp memory
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) PURE; // system memory

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) PURE;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) PURE;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) PURE;

    // surface
    virtual Surface * getBackBuffer( size_t whichBackBuffer ) PURE;

    // texture
    virtual Texture * createTexture( wstring filename ) PURE;


    // Font
    // Sprite

    // destroy
    virtual bool destroyEffectShader( EffectShader *) PURE;
    virtual bool destroyVertexShader( VertexShader *) PURE;
    virtual bool destroyPixelShader( PixelShader *) PURE;
    virtual bool destroyVertexBuffer( VertexBuffer *) PURE;
    virtual bool destroyIndexBuffer( IndexBuffer *) PURE;
    virtual bool destroySurface( Surface * ) PURE;
    virtual bool destroyTexture( Texture * ) PURE;

};


}
