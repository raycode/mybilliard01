#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderState_AlphaDX9Imp::RenderState_AlphaDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
: d3d9Device_( d3d9Device )
{
}

void RenderState_AlphaDX9Imp::setColorBufferTurnOff()
{
    //d3d9Device_->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
    //d3d9Device_->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
}

void RenderState_AlphaDX9Imp::setColorBufferTurnOn()
{
    //d3d9Device_->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
    //d3d9Device_->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE );
}

}