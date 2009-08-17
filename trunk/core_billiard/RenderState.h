#pragma once
namespace my_render {


MY_INTERFACE RenderState {
    virtual ~RenderState() {}

    virtual const RenderState_Wireframe * getWireframe() const = 0;
    virtual RenderState_Wireframe * setWireframe() = 0;

    virtual const RenderState_Cull * getCull() const = 0;
    virtual RenderState_Cull * setCull() = 0;

    //virtual void setRenderState_Alpha( RenderState_Alpha * state ) = 0;
    //virtual void setRenderState_PolygonOffset( RenderState_PolygonOffset * state ) = 0;
    //virtual void setRenderState_Stencil( RenderState_Stencil * state ) = 0;
    //virtual void setRenderState_ZBuffer( RenderState_ZBuffer * state ) = 0;


};

}