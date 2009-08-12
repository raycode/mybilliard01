#pragma once
namespace my_render {


class NullRenderEventListener : IMPLEMENTS_( RenderEventListener ) {
public:
    virtual void init( Render * render ) OVERRIDE {}
    virtual void displayReset( Render * render, int x, int y, int width, int height ) OVERRIDE {}
    virtual void update( float elapsedTime ) OVERRIDE {}
    virtual void display( Render * render ) OVERRIDE {}
    virtual void displayLost( Render * render ) OVERRIDE {}
    virtual void destroy( Render * render ) OVERRIDE {}

};


}