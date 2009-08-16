#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE_( Base ) {

    virtual void draw( Render * render ) = 0;

};


}
