#pragma once
namespace my_render {


MY_INTERFACE RenderBufferFactory {
    virtual ~RenderBufferFactory() {}

    // shader
    virtual EffectShader * createEffectShader( wstring filename ) = 0;

    virtual VertexShader * createVertexShader_1_1( wstring filename, wstring entry ) = 0;
    virtual VertexShader * createVertexShader_2_0( wstring filename, wstring entry ) = 0;
    virtual VertexShader * createVertexShader_2_0_sw( wstring filename, wstring entry ) = 0;

    virtual PixelShader * createPixelShader_2_0( wstring filename, wstring entry ) = 0;
    virtual PixelShader * createPixelShader_2_sw( wstring filename, wstring entry ) = 0;

    // vertex buffer, index buffer
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) = 0; // video memory
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) = 0; // agp memory
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) = 0; // system memory

    virtual IndexBuffer * createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) = 0;
    virtual IndexBuffer * createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) = 0;
    virtual IndexBuffer * createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) = 0;

    // surface
    virtual Surface * getBackBuffer( size_t whichBackBuffer ) = 0;

    // texture
    virtual Texture * createTexture( wstring filename ) = 0;


    // Font
    // Sprite

    // release
    virtual bool releaseEffectShader( EffectShader *) = 0;
    virtual bool releaseVertexShader( VertexShader *) = 0;
    virtual bool releasePixelShader( PixelShader *) = 0;
    virtual bool releaseVertexBuffer( VertexBuffer *) = 0;
    virtual bool releaseIndexBuffer( IndexBuffer *) = 0;
    virtual bool releaseSurface( Surface * ) = 0;
    virtual bool releaseTexture( Texture * ) = 0;

};


}
