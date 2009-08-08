#pragma once
namespace my_render {


enum ELookAt
{
    ELookAtLook,
    ELookAtEye,
    ELookAtUp
};


INTERFACE_ Camera : public Base {
public:

public: virtual ~Camera() {}
};


}
