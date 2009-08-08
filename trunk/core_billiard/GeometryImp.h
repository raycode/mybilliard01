#pragma once
namespace my_render_imp {


class GeometryImp : public BaseImp, IMPLEMENTS_( Geometry ) {
public:
    virtual void draw( Render * render );
};


}