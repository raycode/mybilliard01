#pragma once
#include "stdafx.h"

namespace my_render {
    using namespace std;

    class Render;
    class RenderEventListener;
    class RenderErrorListener;
    class NullRenderEventListener;
    class NullRenderErrorListener;
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
    class GeometryMesh;
    class GeometryMeshPrimitive;


    MY_SMART_PTR( Render );
    MY_SMART_PTR( RenderEventListener );
    MY_SMART_PTR( RenderErrorListener );
    MY_SMART_PTR( NullRenderEventListener );
    MY_SMART_PTR( NullRenderErrorListener );
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
    MY_SMART_PTR( GeometryMesh );
    MY_SMART_PTR( GeometryMeshPrimitive );
}

#include "RenderErrorListener.h"
#include "RenderEventListener.h"
#include "NullRenderErrorListener.hpp"
#include "NullRenderEventListener.hpp"
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
#include "GeometryMesh.h"
#include "GeometryMeshPrimitive.h"

