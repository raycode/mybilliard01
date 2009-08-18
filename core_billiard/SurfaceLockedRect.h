#pragma once
namespace my_render {


MY_INTERFACE SurfaceLockedRect {
    virtual ~SurfaceLockedRect() {}

    virtual int getPitch() PURE;
    virtual void * getBitPointer() PURE;

};


}
