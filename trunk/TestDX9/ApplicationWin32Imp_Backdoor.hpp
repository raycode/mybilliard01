#pragma once

struct ApplicationWin32Imp::TestingBackdoor {
    PRIVATE_METHOD_0( bool, ApplicationWin32Imp, createWindow );
    PRIVATE_METHOD_0( bool, ApplicationWin32Imp, isWindowCreated );
    PRIVATE_METHOD_0_VOID( ApplicationWin32Imp, destroyWindow );
    PRIVATE_METHOD_0_VOID( ApplicationWin32Imp, mainLoop );
    PRIVATE_METHOD_4( LRESULT, ApplicationWin32Imp, MsgProc, HWND, UINT, WPARAM, LPARAM );
    PRIVATE_METHOD_4( void, ApplicationWin32Imp, MsgProcKeyboard, HWND, UINT, WPARAM, LPARAM );
};

