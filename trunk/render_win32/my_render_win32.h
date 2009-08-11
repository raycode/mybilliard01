#pragma once
#include "../core_billiard/my_render.h"

namespace my_render_win32 {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;

    class ApplicationWin32;
    class Win32MessageListener;
    class NullWin32MessageListener;

    class RenderWin32;
    class NullRenderWin32;

    MY_SMART_PTR( ApplicationWin32 );
    MY_SMART_PTR( Win32MessageListener );
    MY_SMART_PTR( NullWin32MessageListener );
    MY_SMART_PTR( RenderWin32 );
    MY_SMART_PTR( NullRenderWin32 );
}

#include "Win32MessageListener.h"
#include "NullWin32MessageListener.hpp"
#include "RenderWin32.h"
#include "NullRenderWin32.hpp"
#include "ApplicationWin32.h"
