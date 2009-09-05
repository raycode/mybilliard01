#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ) {

    virtual GeometryMesh * getMesh() PURE;

};


}
