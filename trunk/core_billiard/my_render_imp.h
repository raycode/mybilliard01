#pragma once

#include "my_render.h"
#include "MySmartPtr.h"
#include "MyUtilities.h"

namespace my_render_imp {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;

    MY_SMART_PTR( DAE );

    class RenderImp;
    class SceneImp;
    class NodeImp;

    class GeometryImp;

    class InstanceImp;
    class InstanceGeometryImp;

    MY_SMART_PTR( SceneImp );
    MY_SMART_PTR( NodeImp );
}

#include "RenderImp.h"
#include "SceneImp.h"
#include "NodeImp.h"

#include "GeometryImp.h"

#include "InstanceImp.h"
#include "InstanceGeometryImp.h"
