#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


DepthStensilDX9Imp::DepthStensilDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height, bool discard, D3DPOOL pool )
: d3d9Device_( d3d9Device )
, width_( width )
, height_( height )
, discard_( discard )
, pool_( pool )
{
}

bool DepthStensilDX9Imp::acquireResource()
{
    LPDIRECT3DSURFACE9 newSurfaceDX9;
    const DXUTDeviceSettings d3dSettings = DXUTGetDeviceSettings();
    const HRESULT hr = getD3D9Device()->CreateDepthStencilSurface(
        width_, height_,
        d3dSettings.d3d9.pp.AutoDepthStencilFormat,
        D3DMULTISAMPLE_NONE, 0,
        discard_, & newSurfaceDX9, NULL );
    RETURN_FALSE_IF_FAILED( hr, L"DepthStensilDX9Imp::acquireResource" );

    surface_ = SurfaceDX9Ptr( new SurfaceDX9Imp( IDirect3DSurface9Ptr( newSurfaceDX9 ) ) );
    return true;
}

void DepthStensilDX9Imp::releaseResource() {
    surface_.reset();
}
SurfaceDX9 * DepthStensilDX9Imp::getSurfaceDX9() {
    return surface_.get();
}
LPDIRECT3DDEVICE9 DepthStensilDX9Imp::getD3D9Device() {
    return d3d9Device_;
}

}