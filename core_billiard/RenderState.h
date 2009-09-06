#pragma once
namespace my_render {


MY_INTERFACE RenderState {
    virtual ~RenderState() {}

    virtual const RenderState_Wireframe * getWireframe() const PURE;
    virtual RenderState_Wireframe * setWireframe() PURE;

    virtual const RenderState_Cull * getCull() const PURE;
    virtual RenderState_Cull * setCull() PURE;

    virtual const RenderState_ZBuffer * getZBuffer() const PURE;
    virtual RenderState_ZBuffer * setZBuffer() PURE;

    virtual const RenderState_Alpha * getAlpha() const PURE;
    virtual RenderState_Alpha * setAlpha() PURE;

    //virtual void setRenderState_PolygonOffset( RenderState_PolygonOffset * state ) PURE;
    //virtual void setRenderState_Stencil( RenderState_Stencil * state ) PURE;


};

}