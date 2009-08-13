#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


Geometry * GeometryFactoryImp::createGeometry( domGeometryRef geo ) {
    const wstring id = convertString( geo->getId() );
    const wstring name = convertString( geo->getName() );
    const wstring uri = convertString( geo->getDocumentURI()->getURI() );

    domMesh * const mesh = geo->getMesh();
    domConvex_mesh * const convexMesh = geo->getConvex_mesh();
    domSpline * const spline = geo->getSpline();
    if( ! ( mesh || convexMesh || spline ) ) return NULL;

    GeometryImp * const newGeo = createGeometry( id, name, uri );
    if( NULL == newGeo ) return NULL;

    GeometryMeshImp * const newMesh = (NULL == mesh ? NULL : createMesh( mesh ) );
    void * const newConvexMesh = (NULL == convexMesh ? NULL : createConvexMesh( convexMesh ) );
    void * const newSpline = (NULL == spline ? NULL : createSpline( spline ) );
    if( ! (newMesh || newConvexMesh || newSpline) ) {
        release( newGeo );
        return NULL;
    }

    newGeo->setMesh( newMesh );
    //newGeo->setConvexMesh( newConvexMesh );
    //newGeo->setSpline( newSpline );
    return newGeo;
}

GeometryImp * GeometryFactoryImp::createGeometry( wstring id, wstring name, wstring uri ) {
    if( NULL != find( id ) ) return NULL;

    GeometryImp * const newGeo = new GeometryImp();
    if( NULL == newGeo ) return NULL;

    createdObjects_.push_back( GeometryImpPtr( newGeo ) );

    newGeo->setID( id );
    newGeo->setName( name );
    newGeo->setURI( uri );

    return newGeo;
}

GeometryMeshImp * GeometryFactoryImp::createGeometryMesh() {
    GeometryMeshImp * const newMesh = new GeometryMeshImp();
    if( NULL == newMesh ) return NULL;

    meshs_.push_back( GeometryMeshImpPtr( newMesh ) );

    return newMesh;
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createGeometryMeshPrimitive( wstring name, size_t triangleCount, wstring materialName, int primitiveTypeID )
{
    GeometryMeshPrimitiveImp * const newPrim = new GeometryMeshPrimitiveImp();
    if( NULL == newPrim ) return NULL;

    primitives_.push_back( GeometryMeshPrimitiveImpPtr( newPrim ) );

    newPrim->setName( name );
    newPrim->setTriangleCount( triangleCount );
    newPrim->setMaterialName( materialName );
    newPrim->setRenderingPrimitiveType( primitiveTypeID );

    return newPrim;
}

Geometry * GeometryFactoryImp::find( wstring id ) {
    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

void GeometryFactoryImp::release( Geometry * ptr ) {
    releaseGeometry( ptr );
}

void GeometryFactoryImp::releaseGeometry( Geometry * ptr ) {
    if( NULL == ptr ) return;

    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (&**iter) != ptr ) continue;

        releaseGeometryMesh( (*iter)->getMesh() );
        createdObjects_.erase( iter );
        break;
    }
}

void GeometryFactoryImp::releaseGeometryMesh( GeometryMesh * ptr ) {
    if( NULL == ptr ) return;

    MY_FOR_EACH( Meshs, iter, meshs_ ) {
        if( (&**iter) != ptr ) continue;

        for( size_t i = 0; i < (*iter)->getNumPrimitives(); ++i )
            releaseGeometryMeshPrimitive( (*iter)->getPrimitive( i ) );

        meshs_.erase( iter );
        break;
    }
}

void GeometryFactoryImp::releaseGeometryMeshPrimitive( GeometryMeshPrimitive * ptr ) {
    if( NULL == ptr ) return;

    MY_FOR_EACH( Primitives, iter, primitives_ ) {
        if( (&**iter) != ptr ) continue;

        primitives_.erase( iter );
        break;
    }
}

GeometryFactoryImp::GeometryFactoryImp( InstanceResolver * instanceResolver )
: instanceResolver_( instanceResolver )
{
}

void * GeometryFactoryImp::createConvexMesh( domConvex_meshRef ) {
    // TODO
    return NULL;
}

void * GeometryFactoryImp::createSpline( domSplineRef ) {
    // TODO
    return NULL;
}

struct GeometryFactoryImp::Pimpl {

    template<
        typename TDom,
        typename TFactory
    >
    static void readPrimitives(
        GeometryMeshImp * newMesh,
        daeTArray< daeSmartRef< typename TDom > > & primitiveArray,
        TFactory * factory,
        GeometryMeshPrimitiveImp * (TFactory::*funcCreateMesh)( daeSmartRef< typename TDom > )
    )
    {
        const size_t numPrimitiveArray = primitiveArray.getCount();
        for( size_t i = 0; i < numPrimitiveArray; ++i )
        {
            TDom * const primitive = primitiveArray[ i ];
            GeometryMeshPrimitiveImp * const newPrim = (*factory.*(funcCreateMesh))( primitive );
            if( NULL == newPrim ) continue;

            newMesh->appendPrimitive( newPrim );
        }
    }
};

GeometryMeshImp * GeometryFactoryImp::createMesh( domMeshRef mesh )
{
    GeometryMeshImp * const newMesh = createGeometryMesh();
    if( NULL == newMesh ) return NULL;

    Pimpl::readPrimitives( newMesh, mesh->getPolygons_array(), this, &GeometryFactoryImp::createPrimitive_polygons );
    Pimpl::readPrimitives( newMesh, mesh->getPolylist_array(), this, &GeometryFactoryImp::createPrimitive_polylist );
    Pimpl::readPrimitives( newMesh, mesh->getTriangles_array(), this, &GeometryFactoryImp::createPrimitive_triangles );
    Pimpl::readPrimitives( newMesh, mesh->getTrifans_array(), this, &GeometryFactoryImp::createPrimitive_trifans );
    Pimpl::readPrimitives( newMesh, mesh->getTristrips_array(), this, &GeometryFactoryImp::createPrimitive_tristrips );
    Pimpl::readPrimitives( newMesh, mesh->getLines_array(), this, &GeometryFactoryImp::createPrimitive_lines );
    Pimpl::readPrimitives( newMesh, mesh->getLinestrips_array(), this, &GeometryFactoryImp::createPrimitive_linestrips );

    return newMesh;
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_polygons( domPolygonsRef polygon )
{
    const wstring name = convertString( polygon->getName() );
    const size_t numTriangle = (size_t) polygon->getCount();
    const wstring materialName = convertString( polygon->getMaterial() );

    GeometryMeshPrimitiveImp * const newPrim = createGeometryMeshPrimitive( name, numTriangle, materialName, domPolygons::ID() );
    if( NULL == newPrim ) return NULL;

    GeometryMeshInput input( polygon->getInput_array() );
    const size_t numTexture = input.getNumTexture();
    domP_Array p = polygon->getP_array();

    for( size_t i = 0; i < p.getCount(); ++i )
    {
        assert( 0 == (p[ i ]->getValue().getCount() % 3) );
        input.setIndexies( p[ i ]->getValue() );

        while( input.hasNext() )
        {
            input.getNext();
            newPrim->appendPosition( input.getVertex() );
            if( input.hasNormal() ) newPrim->appendNormal( input.getNormal() );
            if( input.hasBinormal() ) newPrim->appendBinormal( input.getBinormal() );
            if( input.hasTangent() ) newPrim->appendTangent( input.getTangent() );
            if( input.hasColor() ) newPrim->appendColor( input.getColor() );

            for( size_t tex = 0; tex < numTexture; ++tex )
                newPrim->appendTexCoord( input.getTexCoord( tex ), tex );

            newPrim->appendIndex( newPrim->getNumVertex() -1 );
        }
    }

    return newPrim;
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_polylist( domPolylistRef ) {
    // TODO
    return NULL;   
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_triangles( domTrianglesRef ) {
    // TODO
    return NULL;   
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_trifans( domTrifansRef ) {
    // TODO
    return NULL;   
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_tristrips( domTristripsRef ) {
    // TODO
    return NULL;   
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_lines( domLinesRef ) {
    // TODO
    return NULL;   
}

GeometryMeshPrimitiveImp * GeometryFactoryImp::createPrimitive_linestrips( domLinestripsRef ) {
    // TODO
    return NULL;   
}

//bool GeometryFactoryImp::SetVertexData(GeometryMeshOffset& offset, GeometryMeshImp * newMesh, domListOfUInts &values, size_t i)
//{
//    {
//        NxVec3 pos;
//        domUint index = values[i*offset.max_offset + offset.position_offset];
//        pos.x = (NxReal) (*offset.position_floats)[(size_t)index*3+0];
//        pos.y = (NxReal) (*offset.position_floats)[(size_t)index*3+1];
//        pos.z = (NxReal) (*offset.position_floats)[(size_t)index*3+2];
//        newMesh->appendPosition( pos );
//    }
//
//    if (offset.normal_offset != -1)
//    {
//        NxVec3 normal;
//        domUint index = values[i*offset.max_offset + offset.normal_offset];
//        normal.x = (NxReal) (*offset.normal_floats)[(size_t)index*3+0];
//        normal.y = (NxReal) (*offset.normal_floats)[(size_t)index*3+1];
//        normal.z = (NxReal) (*offset.normal_floats)[(size_t)index*3+2];
//        newMesh->appendNormal( normal );
//    }
//
//    if (offset.texture1_offset != -1)
//    {
//        NxReal u, v;
//        domUint index = values[i*offset.max_offset + offset.texture1_offset];
//        u = (NxReal) (*offset.texture1_floats)[(size_t)index*2+0];
//        v = (NxReal) (*offset.texture1_floats)[(size_t)index*2+1];
//        newMesh->appendTexCoord2D( u, v );
//    }
//
//    return true;
//}


}
