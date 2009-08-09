#pragma once
namespace my_render {


INTERFACE_ RenderErrorNotify {
public:
    virtual void openWindow( wstring ) = 0;

public: virtual ~RenderErrorNotify() {}
};


}
