#pragma once
namespace my_render {


INTERFACE_ RenderEventListener {
public:
    virtual void display( Render * render ) = 0;
    virtual void displayChanged( Render * render, bool modeChanged, bool deviceChanged) = 0;
    virtual void init( Render * render ) = 0;
    virtual void reshape( Render * redner, int x, int y, int width, int height ) = 0;

public: virtual ~RenderEventListener() {}
};


}
