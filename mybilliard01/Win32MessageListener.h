#pragma once
namespace my_render_d3d9_imp {


//==============================================
// !!!! This interface works only for windows.
//==============================================


INTERFACE_ Win32MessageListener {
public:
    // return false when it need to stop default MsgProc.
    virtual bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;

public: virtual ~Win32MessageListener() {}
};


}