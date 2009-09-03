#pragma once


class PostEffectImp
    : IMPLEMENTS_INTERFACE( PostEffect )
    , IMPLEMENTS_INTERFACE( EffectShaderCallBack )
{
public: // from RenderTarget
    virtual bool displayOnRenderTarget( Render * render, RenderTargetCallBack * ) OVERRIDE;
    virtual Texture * getTexture() OVERRIDE;

public: // from RenderTargetCallBack
    virtual void displayOnRenderTargetCallBack( Render * render ) OVERRIDE;

public: // from EffectShaderCallBack
    virtual void displayPass( size_t pass ) OVERRIDE;

public:
    PostEffectImp( RenderBufferFactory *, wstring effectFilename,
        size_t width, size_t height, wstring outputWidthInverse, wstring outputHeightInverse,
        wstring inputTextureName, wstring inputWidthInverse, wstring inputHeightInverse );

private:
    void createQuadVertexBuffer( RenderBufferFactory * );

private:
    EffectShader * effect_;
    RenderTarget * renderTarget_;
    VertexBuffer * quadVertexBuffer_;

    ShaderVariable * inputWidthInv_;
    ShaderVariable * inputHeightInv_;
};

