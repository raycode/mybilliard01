#pragma once
namespace my_render_win32_dx9_imp {


class RenderTargetDX9Imp : IMPLEMENTS_INTERFACE( RenderTargetDX9 ) {
public: // from RenderTarget
    virtual bool displayOnRenderTarget( Render * render, RenderTargetCallBack * ) OVERRIDE;

    virtual Texture * getRenderTargetTexture() OVERRIDE;

public: // from RenderTargetDX9
    virtual TextureDX9 * getTextureDX9() OVERRIDE;
    virtual DepthStensilDX9 * getDepthStensilDX9() OVERRIDE;

public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    RenderTargetDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

private:
    LPDIRECT3DDEVICE9 d3d9Device_;
    size_t width_, height_;

private:
    TextureDX9Ptr texture_;
    DepthStensilDX9Ptr depthStensil_;
};

}
