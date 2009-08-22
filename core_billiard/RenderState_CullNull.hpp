#pragma once
namespace my_render {


NULL_OBJECT( RenderState_Cull ) {

    virtual void setNone() OVERRIDE {}
    virtual void setClockWise() OVERRIDE {}
    virtual void setCounterClockWise() OVERRIDE {}

};

}