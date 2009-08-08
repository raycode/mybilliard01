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
    class GeometryImp;

    class InstanceImp;
    class FactoryImp;
    class NodeFactoryImp;
    class GeometryFactoryImp;

    class RenderMatrix;

    MY_SMART_PTR( NodeImp );
    MY_SMART_PTR( GeometryImp );
    MY_SMART_PTR( InstanceImp );
    MY_SMART_PTR( FactoryImp );
    MY_SMART_PTR( NodeFactoryImp );
    MY_SMART_PTR( GeometryFactoryImp );

    template< typename T > 
    inline T* renderDowncast( Base * abstractObject ) {
        return dynamic_cast< T* >( abstractObject );
    }
}

#include "RenderImp.h"
#include "SceneImp.h"

#include "NodeImp.h"
#include "GeometryImp.h"

#include "FactoryImp.h"
#include "NodeFactoryImp.h"
#include "GeometryFactoryImp.h"
#include "InstanceImp.h"

#include "RenderMatrix.h"