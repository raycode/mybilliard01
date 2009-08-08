#pragma once
namespace my_render_imp {

class RenderMatrix {
public:
    RenderMatrix( Render * render );
    ~RenderMatrix();

    void mult( NxMat34 );

private:
    Render * render_;
};

}