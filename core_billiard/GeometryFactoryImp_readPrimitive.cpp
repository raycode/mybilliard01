#include "Stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


struct GeometryFactoryImp::Pimpl {

    template< typename DomType_ >
    static GeometryMeshPrimitiveImp * createGeometryMeshPrimitive( DomType_ * primitive, GeometryFactoryImp * myThis ) {
        const wstring name = convertString( primitive->getName() );
        const size_t numTriangle = (size_t) primitive->getCount();
        const wstring materialName = convertString( primitive->getMaterial() );

        return myThis->createGeometryMeshPrimitive( name, numTriangle, materialName, DomType_::ID() );
    }

    template< typename DomType_ >
    static bool readPrimitive_P_Array( GeometryMesh * newMesh,
        const daeTArray< daeSmartRef< typename DomType_ > > & primitiveArray,
        GeometryFactoryImp * myThis,
        bool bPositionOnly )
    {
        bool bRst = false;
        for( size_t i = 0; i < primitiveArray.getCount(); ++i )
        {
       
            DomType_ * const primitive = primitiveArray[ i ];
            GeometryMeshPrimitiveImp * const newPrimitive = createGeometryMeshPrimitive( primitive, myThis );
            if( NULL == newPrimitive ) continue;

            const bool succeed = myThis->readGeometryMeshPrimitiveVertices( newPrimitive, primitive->getInput_array(), primitive->getP_array(), bPositionOnly );
            if( false == succeed ) {
                myThis->destroyGeometryMeshPrimitive( newPrimitive );
                continue;
            }

            newMesh->appendPrimitive( newPrimitive );
            bRst = true;
        }
        return bRst;
    }

    template< typename DomType_ >
    static bool readPrimitive_P( GeometryMesh * newMesh,
        const daeTArray< daeSmartRef< typename DomType_ > > & primitiveArray,
        GeometryFactoryImp * myThis,
        bool bPositionOnly )
    {
        bool bRst = false;
        for( size_t i = 0; i < primitiveArray.getCount(); ++i )
        {
            DomType_ * const primitive = primitiveArray[ i ];
            GeometryMeshPrimitiveImp * const newPrimitive = createGeometryMeshPrimitive( primitive, myThis );
            if( NULL == newPrimitive ) continue;

            domP_Array p_array;
            p_array.append( primitive->getP() );

            const bool succeed = myThis->readGeometryMeshPrimitiveVertices( newPrimitive, primitive->getInput_array(), p_array, bPositionOnly );
            if( false == succeed ) {
                myThis->destroyGeometryMeshPrimitive( newPrimitive );
                continue;
            }

            newMesh->appendPrimitive( newPrimitive );
            bRst = true;
        }
        return bRst;
    }

};

bool GeometryFactoryImp::readGeometryMesh( GeometryMesh * newMesh, domMeshRef mesh, bool bPositionOnly )
{
    if( NULL == newMesh ) return NULL;

    bool bRst = false;
    bRst |= Pimpl::readPrimitive_P_Array( newMesh, mesh->getPolygons_array(), this, bPositionOnly );
    bRst |= Pimpl::readPrimitive_P_Array( newMesh, mesh->getTrifans_array(), this, bPositionOnly );
    bRst |= Pimpl::readPrimitive_P_Array( newMesh, mesh->getTristrips_array(), this, bPositionOnly );
    bRst |= Pimpl::readPrimitive_P_Array( newMesh, mesh->getLinestrips_array(), this, bPositionOnly );

    bRst |= Pimpl::readPrimitive_P( newMesh, mesh->getPolylist_array(), this, bPositionOnly );
    bRst |= Pimpl::readPrimitive_P( newMesh, mesh->getTriangles_array(), this, bPositionOnly );
    bRst |= Pimpl::readPrimitive_P( newMesh, mesh->getLines_array(), this, bPositionOnly );

    return bRst;
}

bool GeometryFactoryImp::readGeometryMeshPrimitiveVertices( GeometryMeshPrimitiveImp * newPrimitive, const domInputLocalOffset_Array & input_array, const domP_Array & p_array, bool bPositionOnly )
{
    assert( newPrimitive );
    const size_t beforeNumberOfPosition = newPrimitive->getNumberOfVertex();

    GeometryMeshInput vertexStream( input_array );

    const size_t numNormalSet = vertexStream.getNumberOfNormalSet();
    const size_t numBiNormalSet = vertexStream.getNumberOfBiNormalSet();
    const size_t numTangentSet = vertexStream.getNumberOfTangentSet();
    const size_t numColorSet = vertexStream.getNumberOfColorSet();
    const size_t numTexCoordSet = vertexStream.getNumberOfTexCoord2DSet();

    MY_FOR_EACH_COLLADA( domP, p, p_array ) {
        for( vertexStream.setNewIndices( (*p)->getValue() ); vertexStream.hasVertex(); vertexStream.moveToNextVertex() ) {

            newPrimitive->appendPosition( vertexStream.getVertex() );
            if( bPositionOnly ) continue;

            for( size_t i = 0; i < numNormalSet; ++i )
                newPrimitive->appendNormal( vertexStream.getNormal( i ), i );

            for( size_t i = 0; i < numBiNormalSet; ++i )
                newPrimitive->appendBinormal( vertexStream.getBinormal( i ), i );

            for( size_t i = 0; i < numTangentSet; ++i )
                newPrimitive->appendTangent( vertexStream.getTangent( i ), i );

            for( size_t i = 0; i < numColorSet; ++i )
                newPrimitive->appendColor( vertexStream.getColor( i ), i );

            for( size_t i = 0; i < numTexCoordSet; ++i )
                newPrimitive->appendTexCoord2D( vertexStream.getTexCoord2D_U( i ),
                                                vertexStream.getTexCoord2D_V( i ), i );
        }
    }

    return (newPrimitive->getNumberOfVertex() != beforeNumberOfPosition);
}



}