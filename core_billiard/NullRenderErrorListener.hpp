#pragma once
namespace my_render {


class NullRenderErrorListener : IMPLEMENTS_( RenderErrorListener ) {
public:
    virtual void createWindow( wstring ) {}
    virtual void createDevice( wstring ) {}
};


}
