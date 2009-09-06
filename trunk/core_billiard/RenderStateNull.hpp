#pragma once
namespace my_render {

NULL_OBJECT( RenderState ) {

    virtual const RenderState_Wireframe * getWireframe() const OVERRIDE { return & nullWireframe_; }
    virtual RenderState_Wireframe * setWireframe() OVERRIDE { return & nullWireframe_; }

    virtual const RenderState_Cull * getCull() const OVERRIDE { return & nullCull_; }
    virtual RenderState_Cull * setCull() OVERRIDE { return & nullCull_; }

    virtual const RenderState_ZBuffer * getZBuffer() const OVERRIDE { return & nullZBuffer_; }
    virtual RenderState_ZBuffer * setZBuffer() OVERRIDE { return & nullZBuffer_; }

    virtual const RenderState_Alpha * getAlpha() const OVERRIDE { return & nullAlpha_; }
    virtual RenderState_Alpha * setAlpha() OVERRIDE { return & nullAlpha_; }

private:
    RenderState_WireframeNull nullWireframe_;
    RenderState_CullNull nullCull_;
    RenderState_AlphaNull nullAlpha_;
    RenderState_ZBufferNull nullZBuffer_;

};

}