#pragma once
namespace my_render_win32 {


MY_INTERFACE ApplicationWin32 : EXTENDS_INTERFACE_( ApplicationWindow ) {

    virtual void addWin32MessageListener( Win32MessageListener * listener ) = 0;
    virtual HWND getHWND() = 0;
};


}