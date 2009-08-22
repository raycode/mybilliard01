#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ) {

    virtual void display() PURE;
    virtual GeometryMesh * getMesh() PURE;

};


}
