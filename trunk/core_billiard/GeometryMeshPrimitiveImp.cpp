#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


GeometryMeshPrimitiveImp::GeometryMeshPrimitiveImp()
: numTriangles_( 0u )
, display_pointer_( & VertexBuffer::DrawPrimitive::TRIANGLELIST )
{
}

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

size_t GeometryMeshPrimitiveImp::getNumberOfVertex() {
    if( semanticSet_[ ETYPE_POSITION ].size() == 0 ) return 0;
    return semanticSet_[ ETYPE_POSITION ][ 0 ].size();
}

void GeometryMeshPrimitiveImp::setRenderingPrimitiveType( const int primitiveTypeID ) {
    primitiveTypeID_ = primitiveTypeID;

    if( primitiveTypeID == domTrifans::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::TRIANGLEFAN;
    else if( primitiveTypeID == domTristrips::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::TRIANGLESTRIP;
    else if( primitiveTypeID == domPolygons::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::TRIANGLELIST;
    else if( primitiveTypeID == domPolylist::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::TRIANGLELIST;
    else if( primitiveTypeID == domTriangles::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::TRIANGLELIST;
    else if( primitiveTypeID == domLinestrips::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::LINESTRIP;
    else if( primitiveTypeID == domLines::ID() )
        display_pointer_ = &VertexBuffer::DrawPrimitive::LINELIST;
    else
        throw exception();
}

void GeometryMeshPrimitiveImp::display() {
    ((vertexBuffer_->drawPrimitive())->*display_pointer_)();
}

void GeometryMeshPrimitiveImp::display_positionOnly() {
    ((vertexBuffer_->drawPrimitive_positionOnly())->*display_pointer_)();
}


void GeometryMeshPrimitiveImp::appendPosition( NxVec3 val ) {
    const size_t whichSet = 0;
    semanticSet_[ ETYPE_POSITION ].resize( std::max( semanticSet_[ ETYPE_POSITION ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_POSITION ][ whichSet ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendNormal( NxVec3 val, size_t whichSet ) {
    semanticSet_[ ETYPE_NORMAL ].resize( std::max( semanticSet_[ ETYPE_NORMAL ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_NORMAL ][ whichSet ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendBinormal( NxVec3 val, size_t whichSet ) {
    semanticSet_[ ETYPE_BINORMAL ].resize( std::max( semanticSet_[ ETYPE_BINORMAL ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_BINORMAL ][ whichSet ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendTangent( NxVec3 val, size_t whichSet ) {
    semanticSet_[ ETYPE_TANGENT ].resize( std::max( semanticSet_[ ETYPE_TANGENT ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_TANGENT ][ whichSet ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendColor( NxVec3 val, size_t whichSet ) {
    semanticSet_[ ETYPE_COLOR ].resize( std::max( semanticSet_[ ETYPE_COLOR ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_COLOR ][ whichSet ].push_back( val );
}

void GeometryMeshPrimitiveImp::appendTexCoord2D( NxReal u, NxReal v, size_t whichSet ) {
    NxVec3 uv;
    uv.x = u;
    uv.y = v;
    semanticSet_[ ETYPE_TEXCOORD_2D ].resize( std::max( semanticSet_[ ETYPE_TEXCOORD_2D ].size(), whichSet + 1) );
    semanticSet_[ ETYPE_TEXCOORD_2D ][ whichSet ].push_back( uv );
}

void GeometryMeshPrimitiveImp::buildDeviceBuffer_onStatic( RenderBufferFactory * renderFactory ) {
    vertexBuffer_ = renderFactory->createVertexBuffer_stream( getNumberOfVertex(), (float*) &(semanticSet_[ ETYPE_POSITION ][ 0 ][ 0 ]) );
    buildDeviceBuffer( vertexBuffer_ );
}
void GeometryMeshPrimitiveImp::buildDeviceBuffer_onDynamic( RenderBufferFactory * renderFactory ) {
    vertexBuffer_ = renderFactory->createVertexBuffer_stream( getNumberOfVertex(), (float*) &(semanticSet_[ ETYPE_POSITION ][ 0 ][ 0 ]) );
    buildDeviceBuffer( vertexBuffer_ );
}
void GeometryMeshPrimitiveImp::buildDeviceBuffer_onStream( RenderBufferFactory * renderFactory ) {
    vertexBuffer_ = renderFactory->createVertexBuffer_stream( getNumberOfVertex(), (float*) &(semanticSet_[ ETYPE_POSITION ][ 0 ][ 0 ]) );
    buildDeviceBuffer( vertexBuffer_ );
}
void GeometryMeshPrimitiveImp::buildDeviceBuffer( VertexBuffer * vertexBuffer ) {
    if( NULL == vertexBuffer ) return;

    for( size_t i = 0; i < semanticSet_[ ETYPE_NORMAL ].size(); ++i )
        vertexBuffer->appendNormal_Array( (float*) &(semanticSet_[ ETYPE_NORMAL ][ i ][ 0 ]), i );
    for( size_t i = 0; i < semanticSet_[ ETYPE_BINORMAL ].size(); ++i )
        vertexBuffer->appendBinormal_Array( (float*) &(semanticSet_[ ETYPE_BINORMAL ][ i ][ 0 ]), i );
    for( size_t i = 0; i < semanticSet_[ ETYPE_TANGENT ].size(); ++i )
        vertexBuffer->appendTangent_Array( (float*) &(semanticSet_[ ETYPE_TANGENT ][ i ][ 0 ]), i );
    for( size_t i = 0; i < semanticSet_[ ETYPE_COLOR ].size(); ++i ) {
        vector< NxU32 > stream;
        MY_FOR_EACH( Semantic, iter, semanticSet_[ ETYPE_COLOR ][ i ] )
            stream.push_back( PixelColor( *iter ) );
        vertexBuffer->appendColor_Array( &(stream[ 0 ]), i );
    }

    for( size_t i = 0; i < semanticSet_[ ETYPE_TEXCOORD_2D ].size(); ++i ) {
        vector< float > stream;
        MY_FOR_EACH( Semantic, iter, semanticSet_[ ETYPE_TEXCOORD_2D ][ i ] ) {
            stream.push_back( iter->x );
            stream.push_back( iter->y );
        }
        vertexBuffer->appendTexCoord2D_Array( (float*) &(stream[ 0 ]), i );
    }
}

}
