#pragma once
namespace my_render {


MY_INTERFACE GeometryFactory {
    virtual ~GeometryFactory() {}

    virtual Geometry * createGeometry( domGeometryRef ) PURE;
    virtual Geometry * find( wstring id ) PURE;
    virtual bool destroyGeometry( Geometry * ) PURE;

};

}
