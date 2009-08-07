#pragma once
namespace my_render {

INTERFACE_ Render {
public:
    virtual void setScreenWidth( int width ) = 0;
    virtual void setScreenHeight( int height ) = 0;

    virtual int getScreenWidth() = 0;
    virtual int getScreenHeight() = 0;

    virtual void setUpAxis( domUpAxisType up ) = 0;
    virtual domUpAxisType getUpAxis() = 0;

    virtual void pushMatrix() = 0;
    virtual void popMatrix() = 0;

public: virtual ~Render() {}
};

}