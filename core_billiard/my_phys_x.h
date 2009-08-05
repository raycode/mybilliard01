#pragma once

#ifdef WIN32 
#	define NOMINMAX
#	include <windows.h>
#endif

#if defined(_XBOX)
#	include <xtl.h>
#endif

#pragma warning ( disable : 4505 4819 )

#include "NxPhysics.h"
#include "PerfRenderer.h"
#include "Timing.h"
#include "NXU_helper.h"

namespace my_phys_x {
    using namespace std;
    using namespace Loki;
    using namespace core_billiard;

}

#include "MyPhysX.h"
#include "ErrorStream.h"
#include "Utilities.h"
