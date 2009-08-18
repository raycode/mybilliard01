#pragma once
namespace my_render_win32 {


MY_INTERFACE ApplicationWin32 : EXTENDS_INTERFACE( ApplicationWindow ) {

    virtual void addWin32MessageListener( Win32MessageListener * listener ) PURE;
    virtual HWND getHWND() PURE;
    virtual const wchar_t * getRegisterClassName() PURE;
};


}