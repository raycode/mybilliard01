#pragma once
namespace my_render_win32 {


class NullRenderWin32 : public NullRender, IMPLEMENTS_( RenderWin32 ) {
public:
    virtual void setHWND( HWND ) {}
};


}
