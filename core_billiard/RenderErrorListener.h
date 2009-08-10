#pragma once
namespace my_render {


INTERFACE_ RenderErrorListener {
public:
    virtual void createWindow( wstring ) = 0;
    virtual void createDevice( wstring ) = 0;

public: virtual ~RenderErrorListener() {}
};


}
