#pragma once
#include "DXUT.h"
//#include "SDKmisc.h"
#include "my_render_win32_dx9.h"
#include "my_render_win32_imp.h"


namespace my_render_win32_dx9_imp {
    using namespace std;
    using namespace my_utility;

    using namespace my_render;
    using namespace my_render_win32;
    using namespace my_render_win32_dx9;

    using namespace my_render_imp;
    using namespace my_render_win32_imp;

    class SurfaceLockedRectDX9Imp;
    class SurfaceDX9Imp;
    class RenderWin32DX9Imp;

    MY_SMART_PTR( SurfaceDX9Imp );
    MY_SMART_PTR( RenderWin32DX9Imp );
    MY_SMART_PTR( SurfaceLockedRectDX9Imp );
}

#include "SurfaceLockedRectDX9Imp.h"
#include "SurfaceDX9Imp.h"
#include "RenderWin32DX9Imp.h"

