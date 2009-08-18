#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


void GeometryMeshImp::display( Render * render ) {
    MY_FOR_EACH( Primitives, primitive, primitives_ ) {
        (*primitive)->display( render );
    }
}

void GeometryMeshImp::appendPrimitive( GeometryMeshPrimitive * primitive ) {
    primitives_.push_back( primitive );
}

size_t GeometryMeshImp::getNumberOfPrimitives() {
    return primitives_.size();
}

GeometryMeshPrimitive * GeometryMeshImp::getPrimitive( size_t index ) {
    return primitives_.at( index );
}


} // namespace
