#pragma once

#pragma warning ( disable : 4819 )
#include "dae.h"
#include "dom/domCOLLADA.h"

#include "MySmartPtr.h"


namespace my_collada {
    using namespace std;
    using namespace Loki;
    using namespace my_utility;

    MY_SMART_PTR( DAE );
}

#include "MyColladaLoader.h"
