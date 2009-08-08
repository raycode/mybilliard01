#pragma once
namespace my_render_imp {

class GeometryFactoryImp : IMPLEMENTS_ GeometryFactory {
public: // from GeometryFactory
    virtual Geometry * createGeometry( domGeometryRef );
    virtual Geometry * find( wstring id );
    virtual void release( Geometry * );

public:
    GeometryFactoryImp( InstanceResolver * instanceResolver );

private:
    InstanceResolver * instanceResolver_;

private:
    typedef list< GeometryPtr > CreatedObjects;
    CreatedObjects createdObjects_;
};

}
