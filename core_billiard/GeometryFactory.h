#pragma once
namespace my_render {

INTERFACE_ GeometryFactory {
public:
    virtual Geometry * createGeometry( domGeometryRef ) = 0;
    virtual Geometry * find( wstring id ) = 0;
    virtual void release( Geometry * ) = 0;

public: virtual ~GeometryFactory() {}
};

}
