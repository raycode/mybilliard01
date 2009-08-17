#pragma once
namespace my_render {


MY_INTERFACE RenderState_Cull {
    virtual ~RenderState_Cull() {}

    virtual void setNone() = 0;

};


}