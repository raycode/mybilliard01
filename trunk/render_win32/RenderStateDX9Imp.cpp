#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderStateDX9Imp::RenderStateDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
: d3d9Device_( d3d9Device )
{
    wireframe_ = RenderState_WireframeDX9Ptr( new RenderState_WireframeDX9Imp( d3d9Device ) );
}

const RenderState_Wireframe * RenderStateDX9Imp::getWireframe() const
{
    return &*wireframe_;
}

RenderState_Wireframe * RenderStateDX9Imp::setWireframe()
{
    return &*wireframe_;
}


}