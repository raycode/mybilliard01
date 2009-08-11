#pragma once
#include "../core_billiard/my_render.h"

#ifndef WIN32
#error "OnlyForWin32"
#endif


namespace my_render_win32 {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;

    class ApplicationWin32;
    class Win32MessageListener;
    class NullWin32MessageListener;

    class RenderWin32;

    MY_SMART_PTR( ApplicationWin32 );
    MY_SMART_PTR( Win32MessageListener );
    MY_SMART_PTR( NullWin32MessageListener );
    MY_SMART_PTR( RenderWin32 );
}

#include "Win32MessageListener.h"
#include "NullWin32MessageListener.h"
#include "RenderWin32.h"
#include "ApplicationWin32.h"
