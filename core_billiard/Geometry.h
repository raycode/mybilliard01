#pragma once
namespace my_render {


MY_INTERFACE Geometry : EXTENDS_INTERFACE( Base ) {

    virtual void draw( Render * render ) = 0;

};


}
