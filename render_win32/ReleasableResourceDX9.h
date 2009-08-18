#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ReleasableResourceDX9 {
    virtual ~ReleasableResourceDX9() {}

    virtual bool acquireResource() PURE;
    virtual void releaseResource() PURE;

};


}