#pragma once
namespace my_render {


INTERFACE_ Geometry : EXTENDS_INTERFACE_( Base ) {
public:
    virtual void draw( Render * render ) = 0;

public: virtual ~Geometry() {}
};


}
