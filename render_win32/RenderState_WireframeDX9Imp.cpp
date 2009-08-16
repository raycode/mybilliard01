#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderState_WireframeDX9Imp::RenderState_WireframeDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
: d3d9Device_( d3d9Device )
{}

void RenderState_WireframeDX9Imp::setSolid()
{
    d3d9Device_->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
}

void RenderState_WireframeDX9Imp::setWired()
{
    d3d9Device_->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
}

bool RenderState_WireframeDX9Imp::isSolid() const
{
    DWORD val;
    d3d9Device_->GetRenderState( D3DRS_FILLMODE, & val );
    return D3DFILL_WIREFRAME == val;
}


}