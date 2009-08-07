#pragma once
namespace my_render_imp {


class GeometryImp : IMPLEMENTS_ Geometry {
public:
    virtual void draw( Render * render );
};


}