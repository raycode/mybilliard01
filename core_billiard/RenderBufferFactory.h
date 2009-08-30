#pragma once
namespace my_render {


MY_INTERFACE RenderBufferFactory {
    virtual ~RenderBufferFactory() {}

    // shader
    virtual EffectShader * createEffectShader( wstring filename ) PURE;

    // vertex buffer, index buffer
    virtual VertexBuffer * createVertexBuffer_static( size_t numberOfPosition, const float * positions ) PURE; // video memory
    virtual VertexBuffer * createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) PURE; // agp memory
    virtual VertexBuffer * createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) PURE; // system memory

    // texture
    virtual Texture * createTexture( wstring filename ) PURE;
    virtual Texture * createRenderTargetTexture( size_t width, size_t height ) PURE;

    // Font
    // Sprite

    // destroy
    virtual bool destroyEffectShader( EffectShader *) PURE;
    virtual bool destroyVertexBuffer( VertexBuffer *) PURE;
    virtual bool destroyTexture( Texture * ) PURE;

public: // releaser

    struct Destroyer
    {
    public:
        void operator()( Texture * texture ) { owner_->destroyTexture( texture ); }
        void operator()( EffectShader * effect ) { owner_->destroyEffectShader( effect ); }

    public: Destroyer( RenderBufferFactory * owner ) : owner_( owner ) {}
    private: RenderBufferFactory * const owner_;
    };

};


}
