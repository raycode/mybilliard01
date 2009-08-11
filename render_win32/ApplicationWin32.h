#pragma once
namespace my_render_win32 {


INTERFACE_ ApplicationWin32 : EXTENDS_INTERFACE_( ApplicationWindow ) {
public:
    virtual void addWin32MessageListener( Win32MessageListener * listener ) = 0;
    virtual HWND getHWND() = 0;
};


}