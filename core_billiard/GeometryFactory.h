#pragma once
namespace my_render {


MY_INTERFACE GeometryFactory {
    virtual ~GeometryFactory() {}

    virtual Geometry * createGeometry( domGeometryRef ) = 0;
    virtual Geometry * find( wstring id ) = 0;
    virtual void release( Geometry * ) = 0;

};

}
