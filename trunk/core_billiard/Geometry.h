#pragma once
namespace my_render {


INTERFACE_ Geometry : public Base {
public:
    virtual void draw( Render * render ) = 0;

public: virtual ~Geometry() {}
};


}
