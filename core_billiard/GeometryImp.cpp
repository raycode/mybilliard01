#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {

    
GeometryImp::GeometryImp()
    : mesh_( new GeometryMeshImp() )
{
}

void GeometryImp::display() {
    mesh_->display();
}

GeometryMesh * GeometryImp::getMesh() {
    return mesh_.get();
}

}
