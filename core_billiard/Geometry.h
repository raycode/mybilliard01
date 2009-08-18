#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ) {

    virtual void display( Render * render ) PURE;
    virtual GeometryMesh * getMesh() PURE;

};


}
