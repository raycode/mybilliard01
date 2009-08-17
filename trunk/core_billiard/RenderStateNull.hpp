#pragma once
namespace my_render {

NULL_OBJECT( RenderState ) {

    virtual const RenderState_Wireframe * getWireframe() const OVERRIDE { return & nullWireframe_; }
    virtual RenderState_Wireframe * setWireframe() OVERRIDE { return & nullWireframe_; }

    virtual const RenderState_Cull * getCull() const OVERRIDE { return & nullCull_; }
    virtual RenderState_Cull * setCull() OVERRIDE { return & nullCull_; }

private:
    RenderState_WireframeNull nullWireframe_;
    RenderState_CullNull nullCull_;

};

}