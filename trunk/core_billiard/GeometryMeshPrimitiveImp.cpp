#include "my_render_imp.h"
namespace my_render_imp {


wstring GeometryMeshPrimitiveImp::getName() {
    return name_;
}

size_t GeometryMeshPrimitiveImp::getTriangleCount() {
    return numTriangles_;
}

wstring GeometryMeshPrimitiveImp::getMaterialName() {
    return materialName_;
}

void GeometryMeshPrimitiveImp::setName( wstring name ) {
    name_ = name;
}

void GeometryMeshPrimitiveImp::setTriangleCount( size_t siz ) {
    numTriangles_ = siz;
}

void GeometryMeshPrimitiveImp::setMaterialName( wstring materialName ) {
    materialName_ = materialName;
}

GeometryMeshPrimitiveImp::GeometryMeshPrimitiveImp()
: numTriangles_( 0u )
{

}

void GeometryMeshPrimitiveImp::draw( Render * render ) {
    render;
    // TODO
}


}