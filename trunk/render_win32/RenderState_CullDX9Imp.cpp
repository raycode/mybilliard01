#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderState_CullDX9Imp::RenderState_CullDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
    : d3d9Device_( d3d9Device )
{}

void RenderState_CullDX9Imp::setNone() {
    d3d9Device_->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

}


}