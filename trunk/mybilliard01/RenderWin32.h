#pragma once
namespace my_render_win32 {


INTERFACE_ RenderWin32 : EXTENDS_INTERFACE_( Render ) {
public:
    virtual void setHWND( HWND ) = 0;
};

}