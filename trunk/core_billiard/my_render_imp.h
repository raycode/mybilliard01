#pragma once
#include "my_render.h"

namespace my_render_imp {
    using namespace std;
    using namespace std::tr1;
    using namespace my_utility;
    using namespace my_render;

    class SceneImp;
    class BaseImp;
    class PixelColor;

    class NodeImp;
    class NodeAnimation;
    class NodeFactoryImp;

    class GeometryImp;
    class GeometryMeshImp;
    class GeometryMeshInput;
    class GeometryFactoryImp;
    class GeometryMeshPrimitiveImp;

    class CameraImp;
    class CameraFactoryImp;
    class CameraPerspectiveImp;
    class CameraOrthographicImp;

    class InstanceImp;
    class ColladaFactoryImp;

    MY_SMART_PTR( NodeImp );
    MY_SMART_PTR( GeometryImp );
    MY_SMART_PTR( PixelColor );
    MY_SMART_PTR( InstanceImp );
    MY_SMART_PTR( ColladaFactoryImp );
    MY_SMART_PTR( NodeFactoryImp );
    MY_SMART_PTR( GeometryFactoryImp );
    MY_SMART_PTR( NodeAnimation );
    MY_SMART_PTR( GeometryMeshImp );
    MY_SMART_PTR( GeometryMeshInput );
    MY_SMART_PTR( GeometryMeshPrimitiveImp );
    MY_SMART_PTR( CameraImp );
    MY_SMART_PTR( CameraFactoryImp );
    MY_SMART_PTR( CameraPerspectiveImp );
    MY_SMART_PTR( CameraOrthographicImp );

    template< typename T > 
    inline T* renderDowncast( Base * abstractObject ) {
        return dynamic_cast< T* >( abstractObject );
    }
}

#include "ColladaFactoryImp.h"
#include "NodeFactoryImp.h"
#include "InstanceImp.h"

#include "BaseImp.h"
#include "PixelColor.h"

#include "NodeImp.h"
#include "NodeAnimation.h"

#include "GeometryFactoryImp.h"
#include "GeometryImp.h"
#include "GeometryMeshImp.h"
#include "GeometryMeshPrimitiveImp.h"
#include "GeometryMeshInput.h"

#include "SceneImp.h"

#include "CameraCommonImp.h"
#include "CameraPerspectiveImp.h"
#include "CameraOrthographicImp.h"
#include "CameraImp.h"
#include "CameraFactoryImp.h"

#include "WM4Math.h"
#include "RowMajorMatrix44.h"
