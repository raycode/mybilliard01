#include "my_render_imp.h"
namespace my_render_imp {

Node * BaseFactoryImp::createVisualScene( domVisual_sceneRef ) {
    return NULL;
}

Geometry * BaseFactoryImp::createGeometry( domGeometryRef ) {
    return NULL;
}

void BaseFactoryImp::release( Base * ptr ) {
    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (&**iter) != ptr ) continue;

        createdObjects_.erase( iter );
        break;
    }
}

}