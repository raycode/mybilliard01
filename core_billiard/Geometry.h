#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ) {

    virtual void display() PURE;
    virtual void display_positionOnly() PURE;

    virtual GeometryMesh * getMesh() PURE;
    virtual GeometryMesh * getMesh_positionOnly() PURE;

};


}
