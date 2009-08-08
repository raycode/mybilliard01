#include "my_render_imp.h"
namespace my_render_imp {

Geometry * GeometryFactoryImp::createGeometry( domGeometryRef ) {
    // TODO
    return NULL;
}

Geometry * GeometryFactoryImp::find( wstring id ) {
    // TODO
    return NULL;
}

void GeometryFactoryImp::release( Geometry * obj ) {
    if( NULL == obj ) return;

    // TODO
}

GeometryFactoryImp::GeometryFactoryImp( InstanceResolver * instanceResolver )
: instanceResolver_( instanceResolver )
{
}

}
