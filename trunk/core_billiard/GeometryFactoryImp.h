#pragma once
namespace my_render_imp {


class GeometryFactoryImp : IMPLEMENTS_( GeometryFactory ) {
public: // from GeometryFactory
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE;
    virtual Geometry * find( wstring id ) OVERRIDE;
    virtual void release( Geometry * ) OVERRIDE;

public:
    GeometryFactoryImp( InstanceResolver * instanceResolver );

private: // read geometry
    GeometryMeshImp * createMesh( domMeshRef );
    void * createConvexMesh( domConvex_meshRef );
    void * createSpline( domSplineRef );

private: // read mesh
    GeometryMeshPrimitiveImp * createPrimitive_polygons( domPolygonsRef );
    GeometryMeshPrimitiveImp * createPrimitive_polylist( domPolylistRef );
    GeometryMeshPrimitiveImp * createPrimitive_triangles( domTrianglesRef );
    GeometryMeshPrimitiveImp * createPrimitive_trifans( domTrifansRef );
    GeometryMeshPrimitiveImp * createPrimitive_tristrips( domTristripsRef );
    GeometryMeshPrimitiveImp * createPrimitive_lines( domLinesRef );
    GeometryMeshPrimitiveImp * createPrimitive_linestrips( domLinestripsRef );

    bool SetVertexData(GeometryMeshInput& offset, GeometryMeshImp * newMesh, domListOfUInts &values, size_t i);

private:
    InstanceResolver * instanceResolver_;

private: // create geometry
    GeometryImp * createGeometry( wstring id, wstring name, wstring uri );
    void releaseGeometry( Geometry * );

    typedef list< GeometryImpPtr > CreatedObjects;
    CreatedObjects createdObjects_;

private: // create mesh
    GeometryMeshImp * createGeometryMesh();
    void releaseGeometryMesh( GeometryMesh * );

    typedef list< GeometryMeshImpPtr > Meshs;
    Meshs meshs_;

private: // create primitive
    GeometryMeshPrimitiveImp * createGeometryMeshPrimitive( wstring name, size_t triangleCount, wstring materialName, Render::EPrimitiveType );
    void releaseGeometryMeshPrimitive( GeometryMeshPrimitive * ptr );

    typedef list< GeometryMeshPrimitiveImpPtr > Primitives;
    Primitives primitives_;

private: // Pimpl idiom without any member variables.
    struct Pimpl;
};


} // namespace
