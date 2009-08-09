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

size_t GeometryMeshPrimitiveImp::getNumVertex() {
    return positions_.size();
}

void GeometryMeshPrimitiveImp::setRenderingPrimitiveType( Render::EPrimitiveType primitiveType ) {
    primitiveType_ = primitiveType;
}

void GeometryMeshPrimitiveImp::updateVertexIndexBuffers( Render * render ) {

}

void GeometryMeshPrimitiveImp::draw( Render * render ) {
    render;
    // TODO
}

void GeometryMeshPrimitiveImp::appendPosition( NxVec3 val ) {
    positions_.push_back( val );
}

void GeometryMeshPrimitiveImp::appendNormal( NxVec3 val ) {
    normals_.push_back( val );
}

void GeometryMeshPrimitiveImp::appendTexCoord( Tex2D val, size_t index ) {
    multiTex2Ds_.resize( max( index +1, multiTex2Ds_.size() ) );
    multiTex2Ds_[ index ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendBinormal( NxVec3 val ) {
    binormals_.push_back( val );
}

void GeometryMeshPrimitiveImp::appendTangent( NxVec3 val ) {
    tangents_.push_back( val );
}

void GeometryMeshPrimitiveImp::appendColor( NxVec3 val ) {
    colors_.push_back( val );
}

void GeometryMeshPrimitiveImp::appendIndex( VertexIndex val ) {
    vertexIndex_Array_.push_back( val );
}


}