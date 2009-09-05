#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ), EXTENDS_INTERFACE( Displayable ) {

    virtual GeometryMesh * getMesh() PURE;

};


}
