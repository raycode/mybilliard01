#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderState_ZBufferDX9Imp::RenderState_ZBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
: d3d9Device_( d3d9Device )
{
}

void RenderState_ZBufferDX9Imp::setEnable( bool val ) {
    d3d9Device_->SetRenderState( D3DRS_ZENABLE, val );
}
void RenderState_ZBufferDX9Imp::setReadOnly( bool val ) {
    d3d9Device_->SetRenderState( D3DRS_ZWRITEENABLE, ! val );
}

void RenderState_ZBufferDX9Imp::setCompare_Never() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_NEVER );
}
void RenderState_ZBufferDX9Imp::setCompare_Less() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESS );
}
void RenderState_ZBufferDX9Imp::setCompare_Equal() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_EQUAL );
}
void RenderState_ZBufferDX9Imp::setCompare_LessEqual() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_LESSEQUAL );
}
void RenderState_ZBufferDX9Imp::setCompare_Greater() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_GREATER );
}
void RenderState_ZBufferDX9Imp::setCompare_NotEqual() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_NOTEQUAL );
}
void RenderState_ZBufferDX9Imp::setCompare_GreaterEqual() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_GREATEREQUAL );
}
void RenderState_ZBufferDX9Imp::setCompare_Always() {
    d3d9Device_->SetRenderState( D3DRS_ZFUNC, D3DCMP_ALWAYS );
}


}