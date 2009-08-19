#pragma once
namespace my_render {


MY_INTERFACE RenderState_Cull {
    virtual ~RenderState_Cull() {}

    virtual void setNone() PURE;
    virtual void setClockWise() PURE;
    virtual void setCounterClockWise() PURE;

};


}