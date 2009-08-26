#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderStateDX9Imp::RenderStateDX9Imp( LPDIRECT3DDEVICE9 d3d9Device )
: d3d9Device_( d3d9Device )
{
    wireframe_ = RenderState_WireframeDX9Ptr( new RenderState_WireframeDX9Imp( d3d9Device ) );
    cull_ = RenderState_CullDX9Ptr( new RenderState_CullDX9Imp( d3d9Device ) );
}

const RenderState_Wireframe * RenderStateDX9Imp::getWireframe() const
{
    return wireframe_.get();
}

RenderState_Wireframe * RenderStateDX9Imp::setWireframe()
{
    return wireframe_.get();
}

const RenderState_Cull * RenderStateDX9Imp::getCull() const
{
    return cull_.get();
}

RenderState_Cull * RenderStateDX9Imp::setCull()
{
    return cull_.get();
}



}