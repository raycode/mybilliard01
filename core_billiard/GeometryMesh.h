#pragma once
namespace my_render {


MY_INTERFACE GeometryMesh {
    virtual ~GeometryMesh() {}

    virtual void draw( Render * render ) = 0;

};


}
