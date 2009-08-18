#pragma once
namespace my_render {


MY_INTERFACE RenderState {
    virtual ~RenderState() {}

    virtual const RenderState_Wireframe * getWireframe() const = 0;
    virtual RenderState_Wireframe * setWireframe() PURE;

    virtual const RenderState_Cull * getCull() const = 0;
    virtual RenderState_Cull * setCull() PURE;

    //virtual void setRenderState_Alpha( RenderState_Alpha * state ) PURE;
    //virtual void setRenderState_PolygonOffset( RenderState_PolygonOffset * state ) PURE;
    //virtual void setRenderState_Stencil( RenderState_Stencil * state ) PURE;
    //virtual void setRenderState_ZBuffer( RenderState_ZBuffer * state ) PURE;


};

}