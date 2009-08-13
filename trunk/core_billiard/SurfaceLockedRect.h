#pragma once
namespace my_render {


INTERFACE_ SurfaceLockedRect {
public:
    virtual int getPitch() = 0;
    virtual void * getBitPointer() = 0;

public: virtual ~SurfaceLockedRect() {}
};


}
