#pragma once
namespace my_render {


MY_INTERFACE RenderState_Wireframe {
    virtual ~RenderState_Wireframe() {}

    virtual void setSolid() = 0;
    virtual void setWired() = 0;

    virtual bool isSolid() const = 0;

};


}