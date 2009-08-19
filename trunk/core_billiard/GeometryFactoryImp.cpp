#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


GeometryFactoryImp::GeometryFactoryImp( InstanceResolver * instanceResolver )
{
}

Geometry * GeometryFactoryImp::createGeometry( domGeometryRef geo ) {
    const wstring id = convertString( geo->getId() );
    const wstring name = convertString( geo->getName() );
    const wstring uri = convertString( geo->getDocumentURI()->getURI() );
    if( isAlreadyCreated( id ) ) return NULL;

    domMeshRef const mesh = geo->getMesh();
    domConvex_mesh * const convexMesh = geo->getConvex_mesh();
    domSplineRef const spline = geo->getSpline();
    if( ! ( mesh || convexMesh || spline ) ) return NULL;

    Geometry * const newGeo = createGeometry( id, name, uri );
    if( NULL == newGeo ) return NULL;

    const bool bMesh = readGeometryMesh( newGeo->getMesh(), mesh );
    if( false == bMesh ) {
        destroyGeometry( newGeo );
        return NULL;
    }
    return newGeo;
}

Geometry * GeometryFactoryImp::createGeometry( wstring id, wstring name, wstring uri ) {
    if( isAlreadyCreated( id ) ) return NULL;

    GeometryImp * const newGeo = new GeometryImp();
    if( NULL == newGeo ) return NULL;

    geometries_.push_back( GeometryImpPtr( newGeo ) );

    newGeo->setID( id );
    newGeo->setName( name );
    newGeo->setURI( uri );

    return newGeo;
}

bool GeometryFactoryImp::isAlreadyCreated( wstring id ) {
    return NULL != find( id );
}

Geometry * GeometryFactoryImp::find( wstring id ) {
    MY_FOR_EACH( Geometries, iter, geometries_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

bool GeometryFactoryImp::destroyGeometry( Geometry * ptr ) {
    MY_FOR_EACH( Geometries, iter, geometries_ ) {
        if( (&**iter) != ptr ) continue;

        GeometryMesh * const mesh = (*iter)->getMesh();
        const size_t numberOfPrimitives = mesh->getNumberOfPrimitives();
        for( size_t i = 0; i < numberOfPrimitives; ++i )
            destroyGeometryMeshPrimitive( mesh->getPrimitive( i ) );

        geometries_.erase( iter );
        return true;
    }
    return false;
}

bool GeometryFactoryImp::readGeometryConvexMesh( GeometryMesh *, domConvex_meshRef ) {
    return NULL;
}

bool GeometryFactoryImp::readGeometrySpline( GeometryMesh *, domSplineRef ) {
    return NULL;
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createGeometryMeshPrimitive( wstring name, size_t triangleCount, wstring materialName, int primitiveTypeID )
{
    GeometryMeshPrimitiveImp * const newPrim = new GeometryMeshPrimitiveImp();
    if( NULL == newPrim ) return NULL;

    primitives_.push_back( GeometryMeshPrimitivePtr( newPrim ) );

    newPrim->setName( name );
    newPrim->setTriangleCount( triangleCount );
    newPrim->setMaterialName( materialName );
    newPrim->setRenderingPrimitiveType( primitiveTypeID );

    return newPrim;
}

bool GeometryFactoryImp::destroyGeometryMeshPrimitive( GeometryMeshPrimitive * ptr ) {
    MY_FOR_EACH( Primitives, iter, primitives_ ) {
        if( (&**iter) != ptr ) continue;
        primitives_.erase( iter );
        return true;
    }
    return false;
}


}
