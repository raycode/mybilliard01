#pragma once
#include "my_render_win32.h"
#include "../core_billiard/my_render_imp.h"


namespace my_render_win32_imp {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;
    using namespace my_render_win32;

    class ApplicationWin32Imp;

    MY_SMART_PTR( ApplicationWin32Imp );
}

#include "ApplicationWin32Imp.h"
