#pragma once

#include <string>
#include <vector>

#include "NxMat34.h"

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

    class Factory;
    class NodeFactory;
    class GeometryFactory;
    class Instance;
    class InstanceResolver;

    class Geometry;


    MY_SMART_PTR( Render );
    MY_SMART_PTR( Scene );
    MY_SMART_PTR( Base );
    MY_SMART_PTR( Node );
    MY_SMART_PTR( Camera );
    MY_SMART_PTR( Factory );
    MY_SMART_PTR( NodeFactory );
    MY_SMART_PTR( GeometryFactory );
    MY_SMART_PTR( Instance );
    MY_SMART_PTR( InstanceResolver );
    MY_SMART_PTR( Geometry );
}

#include "Render.h"
#include "Scene.h"

#include "Base.h"
#include "Node.h"
#include "Camera.h"

#include "Factory.h"
#include "NodeFactory.h"
#include "GeometryFactory.h"
#include "Instance.h"
#include "InstanceResolver.h"

#include "Geometry.h"

