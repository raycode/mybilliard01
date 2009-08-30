#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE SurfaceLockedRectDX9 {
    virtual ~SurfaceLockedRectDX9() {}

    virtual int getPitch() PURE;
    virtual void * getBitPointer() PURE;

};


}
