#pragma once
namespace my_render {

NULL_OBJECT( RenderState ) {

    virtual const RenderState_Wireframe * getWireframe() const OVERRIDE { return & nullWireframe_; }
    virtual RenderState_Wireframe * setWireframe() OVERRIDE { return & nullWireframe_; }

private:
    RenderState_WireframeNull nullWireframe_;

};

}