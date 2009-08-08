#pragma once

#include <vector>
#include <map>
#include <list>

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

    class FactoryImp;
    class NodeFactoryImp;
    class GeometryFactoryImp;

    class GeometryImp;

    class InstanceImp;
    class InstanceGeometryImp;

    class RenderMatrix;

    MY_SMART_PTR( FactoryImp );
    MY_SMART_PTR( NodeFactoryImp );
    MY_SMART_PTR( GeometryFactoryImp );
    MY_SMART_PTR( SceneImp );
    MY_SMART_PTR( NodeImp );

    template< typename T > 
    inline T* renderDowncast( Base * abstractObject ) {
        return dynamic_cast< T* >( abstractObject );
    }
}

#include "RenderImp.h"
#include "SceneImp.h"
#include "NodeImp.h"

#include "FactoryImp.h"
#include "NodeFactoryImp.h"
#include "GeometryFactoryImp.h"
#include "InstanceImp.h"

#include "GeometryImp.h"

#include "RenderMatrix.h"