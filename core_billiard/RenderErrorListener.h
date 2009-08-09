#pragma once
namespace my_render {


INTERFACE_ RenderErrorListener {
public:
    virtual void openWindow( wstring ) = 0;

public: virtual ~RenderErrorListener() {}
};


}
