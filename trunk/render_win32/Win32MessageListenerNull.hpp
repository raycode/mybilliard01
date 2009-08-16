#pragma once
namespace my_render_win32 {

//==============================================
// !!!! This interface works only for windows.
//==============================================


NULL_OBJECT( Win32MessageListener ) {

    virtual bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) OVERRIDE { return true; }
};


}