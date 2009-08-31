#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderTargetDX9Imp::RenderTargetDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height )
: d3d9Device_( d3d9Device )
, width_( width )
, height_( height )
{
    texture_ = TextureDX9Ptr( new TextureDX9Imp( d3d9Device, width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT ), ReleasableResourceDX9::Destroyer() );

    depthStensil_ = DepthStensilDX9Ptr( new DepthStensilDX9Imp( d3d9Device, width, height, false, D3DPOOL_DEFAULT ), ReleasableResourceDX9::Destroyer() );
}

bool RenderTargetDX9Imp::display( Render * render, RenderTargetCallBack * callBack )
{
    assert( callBack );

    LPDIRECT3DSURFACE9 oldRenderTarget = NULL;
    const HRESULT hr1 = getD3D9Device()->GetRenderTarget( 0, &oldRenderTarget );
    RETURN_FALSE_IF_FAILED( hr1, L"RenderTargetDX9Imp::display" );

    LPDIRECT3DSURFACE9 surface;
    const HRESULT hr2 = getTextureDX9()->getTextureDX9()->GetSurfaceLevel( 0, & surface );
    if( SUCCEEDED( hr2 ) )
    {
        getD3D9Device()->SetRenderTarget( 0, surface );
        SAFE_RELEASE( surface );
    }

    LPDIRECT3DSURFACE9 oldDepthStensil = NULL;
    const HRESULT hr3 = getD3D9Device()->GetDepthStencilSurface( &oldDepthStensil );
    if( SUCCEEDED( hr3 ) )
        getD3D9Device()->SetDepthStencilSurface( getDepthStensilDX9()->getSurfaceDX9()->getSurfaceDX9() );

    {
        CDXUTPerfEventGenerator g( DXUT_PERFEVENTCOLOR, L"Render Target" );
        callBack->display( render );
    }

    if( oldDepthStensil )
    {
        getD3D9Device()->SetDepthStencilSurface( oldDepthStensil );
        oldDepthStensil->Release();
    }

    getD3D9Device()->SetRenderTarget( 0, oldRenderTarget );
    SAFE_RELEASE( oldRenderTarget );
    return true;
}

bool RenderTargetDX9Imp::acquireResource()
{
    if( false == texture_->acquireResource() ) return false;
    if( false == depthStensil_->acquireResource() ) return false;

    return true;
}

void RenderTargetDX9Imp::releaseResource()
{
    texture_.reset();
    depthStensil_.reset();
}

LPDIRECT3DDEVICE9 RenderTargetDX9Imp::getD3D9Device() {
    return d3d9Device_;
}
Texture * RenderTargetDX9Imp::getTexture() {
    return getTextureDX9();
}
TextureDX9 * RenderTargetDX9Imp::getTextureDX9() {
    return texture_.get();
}
DepthStensilDX9 * RenderTargetDX9Imp::getDepthStensilDX9() {
    return depthStensil_.get();
}


}