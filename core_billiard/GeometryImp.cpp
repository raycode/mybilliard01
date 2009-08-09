#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {

void GeometryImp::draw( Render * render ) {
    mesh_->draw( render );
}

void GeometryImp::setMesh( GeometryMesh * newMesh ) {
    mesh_ = newMesh;
}

GeometryImp::GeometryImp()
: mesh_( NULL )
{
}

GeometryMesh * GeometryImp::getMesh() {
    return mesh_;
}

}
