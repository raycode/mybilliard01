#pragma once
namespace my_render {


MY_INTERFACE RenderState_Alpha {
    virtual ~RenderState_Alpha() {}

    virtual void setColorBufferTurnOff() PURE;
    virtual void setColorBufferTurnOn() PURE;

};

}
