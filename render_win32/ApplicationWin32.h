#pragma once
namespace my_render_win32 {


MY_INTERFACE ApplicationWin32 : EXTENDS_INTERFACE( ApplicationWindow ) {

    virtual void addWin32MessageListener( Win32MessageListener * listener ) = 0;
    virtual HWND getHWND() = 0;
    virtual const wchar_t * getRegisterClassName() = 0;
};


}