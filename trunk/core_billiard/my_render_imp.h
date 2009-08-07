#pragma once

#include <vector>
#include <map>

#include "my_render.h"
#include "my_collada.h"

namespace my_render_imp {
    using namespace std;
    using namespace my_collada;
    using namespace my_utility;
    using namespace my_render;

    class RenderImp;
    class SceneImp;
    class NodeImp;

    class GeometryImp;

    class InstanceImp;
    class InstanceGeometryImp;

    class RenderMatrix;

    MY_SMART_PTR( SceneImp );
    MY_SMART_PTR( NodeImp );
}

#include "RenderImp.h"
#include "SceneImp.h"
#include "NodeImp.h"

#include "GeometryImp.h"

#include "InstanceImp.h"
#include "InstanceGeometryImp.h"

#include "RenderMatrix.h"