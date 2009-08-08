#pragma once
namespace my_render_imp {


class GeometryFactoryImp : IMPLEMENTS_( GeometryFactory ) {
public: // from GeometryFactory
    virtual Geometry * createGeometry( domGeometryRef );
    virtual Geometry * find( wstring id );
    virtual void release( Geometry * );

public:
    GeometryFactoryImp( InstanceResolver * instanceResolver );

private: // read geometry
    void readGeometryMesh( domGeometryRef, GeometryImp * newGeo );
    void readGeometryConvexMsh();
    void readGeometrySpline();

private:
    InstanceResolver * instanceResolver_;

private: // create
    GeometryImp * createGeometry();
    typedef list< GeometryImpPtr > CreatedObjects;
    CreatedObjects createdObjects_;
};


} // namespace
