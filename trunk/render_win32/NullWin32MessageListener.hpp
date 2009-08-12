#pragma once
namespace my_render_win32 {

//==============================================
// !!!! This interface works only for windows.
//==============================================


class NullWin32MessageListener : IMPLEMENTS_( Win32MessageListener ) {
public:
    virtual bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) OVERRIDE { return true; }
};


}