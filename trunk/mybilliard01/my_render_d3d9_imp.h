#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "../core_billiard/my_render_imp.h"


#ifndef WIN32
#error "OnlyForWin32"
#endif


namespace my_render_d3d9_imp {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;
    using namespace my_render_imp;

    class Win32MessageListener;
    class NullWin32MessageListener;

    MY_SMART_PTR( Win32MessageListener );
    MY_SMART_PTR( NullWin32MessageListener );
}

#include "Win32MessageListener.h"
#include "NullWin32MessageListener.h"
#include "ApplicationWin32Imp.h"
#include "RenderD3D9Imp.h"

