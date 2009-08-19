#pragma once
#include "stdafx.h"

#pragma warning ( disable : 4505 4819 )

#include "PerfRenderer.h"
#include "Timing.h"
#include "NXU_helper.h"
#include "NXU_ColladaImport.h"
#include "MediaPath.h"

namespace my_phys {
    using namespace std;
    using namespace my_utility;

    class MyPhysX;

    MY_SMART_PTR( MyPhysX );
}

#include "MyPhysX.h"
#include "ErrorStream.h"
#include "Utilities.h"
