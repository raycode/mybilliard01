#include "my_render_imp.h"
namespace my_render_imp {


Geometry * GeometryFactoryImp::createGeometry( domGeometryRef geo ) {
    GeometryImp * const newGeo = createGeometry();
    if( NULL == newGeo ) return NULL;

    readGeometryMesh( geo, newGeo );
    readGeometryConvexMsh();
    readGeometrySpline();

    return newGeo;
}

Geometry * GeometryFactoryImp::find( wstring id ) {
    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

void GeometryFactoryImp::release( Geometry * ptr ) {
    if( NULL == ptr ) return;

    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (&**iter) != ptr ) continue;

        createdObjects_.erase( iter );
        break;
    }
}

GeometryFactoryImp::GeometryFactoryImp( InstanceResolver * instanceResolver )
: instanceResolver_( instanceResolver )
{
}

void GeometryFactoryImp::readGeometryMesh( domGeometryRef geo, GeometryImp * newGeo ) {

}

void GeometryFactoryImp::readGeometryConvexMsh() {
    // TODO
}

void GeometryFactoryImp::readGeometrySpline() {
    // TODO
}


}
