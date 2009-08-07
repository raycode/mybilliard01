#pragma once

#include <string>
#include <vector>

#pragma warning ( disable : 4819 )

#include "dae.h"
#include "dom/domTypes.h"
#include "dom/domCOLLADA.h"

#include "MyUtilities.h"

namespace my_render {
    using namespace std;

    class Render;
    class Scene;

    class Base;
    class Node;
    class Camera;

    class BaseFactory;

    class Geometry;

    class Instance;
    class InstanceGeometry;

    MY_SMART_PTR( Render );
    MY_SMART_PTR( Scene );
    MY_SMART_PTR( Base );
    MY_SMART_PTR( Node );
    MY_SMART_PTR( Camera );
    MY_SMART_PTR( BaseFactory );
    MY_SMART_PTR( Geometry );
    MY_SMART_PTR( Instance );
    MY_SMART_PTR( InstanceGeometry );
}

#include "Base.h"
#include "Render.h"
#include "Scene.h"
#include "Node.h"

#include "BaseFactory.h"

#include "Geometry.h"

#include "Instance.h"
#include "InstanceGeometry.h"


