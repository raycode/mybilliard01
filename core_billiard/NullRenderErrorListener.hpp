#pragma once
namespace my_render {


class NullRenderErrorListener : IMPLEMENTS_( RenderErrorListener ) {
public:
    virtual void createWindow( wstring ) OVERRIDE {}
    virtual void createDevice( wstring ) OVERRIDE {}
};


}
