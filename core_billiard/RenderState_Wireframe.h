#pragma once
namespace my_render {


MY_INTERFACE RenderState_Wireframe {
    virtual ~RenderState_Wireframe() {}

    virtual void setSolid() PURE;
    virtual void setWired() PURE;

    virtual bool isSolid() const = 0;

};


}