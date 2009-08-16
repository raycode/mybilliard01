#pragma once
namespace my_render {


MY_INTERFACE SurfaceLockedRect {
    virtual ~SurfaceLockedRect() {}

    virtual int getPitch() = 0;
    virtual void * getBitPointer() = 0;

};


}
