#pragma once
namespace my_render_win32 {


//==============================================
// !!!! This interface works only for windows.
//==============================================


MY_INTERFACE Win32MessageListener {
    virtual ~Win32MessageListener() {}

    // return false when it need to stop default MsgProc.
    virtual bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) PURE;

};


}