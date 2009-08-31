#pragma once
namespace my_render_win32_dx9_imp {


class DepthStensilDX9Imp : IMPLEMENTS_INTERFACE( DepthStensilDX9 ) {
public: // from DepthStensilDX9
    virtual SurfaceDX9 * getSurfaceDX9() OVERRIDE;

public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    DepthStensilDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height, bool discard, D3DPOOL );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

private:
    LPDIRECT3DDEVICE9 d3d9Device_;
    size_t width_, height_;
    bool discard_;
    D3DPOOL pool_;

private:
    SurfaceDX9Ptr surface_;
};

}