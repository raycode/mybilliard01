#pragma once
namespace my_render_imp {


class RenderImp : IMPLEMENTS_ Render {
public:
    virtual void setScreenWidth( int width );
    virtual void setScreenHeight( int height );

    virtual int getScreenWidth();
    virtual int getScreenHeight();

    virtual void setUpAxis( domUpAxisType up );
    virtual domUpAxisType getUpAxis();

    virtual void pushMatrix();
    virtual void popMatrix();

private:
    domUpAxisType upAxis_;
    int width_, height_;
};

}