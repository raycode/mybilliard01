#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {

    
GeometryImp::GeometryImp()
    : mesh_( new GeometryMeshImp() )
    , mesh_positionOnly_( new GeometryMeshImp() )
{
}

void GeometryImp::display() {
    mesh_->display();
}

void GeometryImp::display_positionOnly() {
    mesh_positionOnly_->display();
}

GeometryMesh * GeometryImp::getMesh() {
    return mesh_.get();
}

GeometryMesh * GeometryImp::getMesh_positionOnly() {
    return mesh_positionOnly_.get();
}

}
