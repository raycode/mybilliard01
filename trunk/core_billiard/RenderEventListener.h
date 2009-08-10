#pragma once
namespace my_render {


INTERFACE_ RenderEventListener {
public:
    virtual void init( Render * render ) = 0;
    virtual void displayReset( Render * render, int x, int y, int width, int height ) = 0;
    virtual void update( float elapsedTime ) = 0;
    virtual void display( Render * render ) = 0;
    virtual void displayLost( Render * render ) = 0;
    virtual void destroy( Render * render ) = 0;

public: virtual ~RenderEventListener() {}
};


}
