#pragma once
namespace my_render_imp {

    class RenderMatrix {
    public:
        RenderMatrix( Render * render );
        ~RenderMatrix();

    private:
        Render * render_;
    };

}