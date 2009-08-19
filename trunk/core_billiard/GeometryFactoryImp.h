#pragma once
namespace my_render_imp {


class GeometryFactoryImp : IMPLEMENTS_INTERFACE( GeometryFactory ) {
public: // from GeometryFactory
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE;
    virtual Geometry * find( wstring id ) OVERRIDE;
    virtual bool destroyGeometry( Geometry * ) OVERRIDE;

public:
    GeometryFactoryImp( InstanceResolver * instanceResolver );

private: // create geometry
    bool readGeometryMesh( GeometryMesh *, domMeshRef );
    bool readGeometryConvexMesh( GeometryMesh *, domConvex_meshRef );
    bool readGeometrySpline( GeometryMesh *, domSplineRef );

    bool readGeometryMeshPrimitiveVertices( GeometryMeshPrimitiveImp *, const domInputLocalOffset_Array &, const domP_Array &);

private: // create geometry
    Geometry * createGeometry( wstring id, wstring name, wstring uri );
    bool isAlreadyCreated( wstring id );

private: // create geometry mesh primitive
    GeometryMeshPrimitiveImp * createGeometryMeshPrimitive( wstring name, size_t triangleCount, wstring materialName, int primitiveTypeID );
    bool destroyGeometryMeshPrimitive( GeometryMeshPrimitive * prim );

private:
    typedef list< GeometryPtr > Geometries;
    Geometries geometries_;

    typedef list< GeometryMeshPrimitivePtr > Primitives;
    Primitives primitives_;

private: // Pimpl idiom without any member variables.
    struct Pimpl;
};


} // namespace
