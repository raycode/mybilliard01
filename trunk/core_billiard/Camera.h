#pragma once
namespace my_render {


INTERFACE_ Camera : public Base {
public:
    virtual void setViewMatrix( const NxMat34 & ) = 0;
    virtual const NxMat34 & getViewMatrix() = 0;

public: virtual ~Camera() {}
};


}
