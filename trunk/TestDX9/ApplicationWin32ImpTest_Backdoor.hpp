#pragma once

#define PRIVATE_METHOD( methodName ) ApplicationWin32Imp::TestingBackdoor::methodName
#define ACCESS_0( returnType, methodName ) static returnType methodName( ApplicationWin32Imp * app ) { return app->methodName(); }
#define ACCESS_4( returnType, methodName, arg0, arg1, arg2, arg3 ) static returnType methodName( ApplicationWin32Imp * app, arg0 a0, arg1 a1, arg2 a2, arg3 a3 ) { return app->methodName( a0, a1, a2, a3 ); }
#define ACCESS_0_VOID( methodName ) static void methodName( ApplicationWin32Imp * app ) { app->methodName(); }

struct ApplicationWin32Imp::TestingBackdoor {
    ACCESS_0( bool, createWindow );
    ACCESS_0( bool, isWindowCreated );
    ACCESS_0_VOID( destroyWindow );
    ACCESS_0_VOID( mainLoop );
    ACCESS_4( LRESULT, MsgProc, HWND, UINT, WPARAM, LPARAM );
    ACCESS_4( void, MsgProcKeyboard, HWND, UINT, WPARAM, LPARAM );
};

