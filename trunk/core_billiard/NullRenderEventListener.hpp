#pragma once
namespace my_render {


class NullRenderEventListener : IMPLEMENTS_( RenderEventListener ) {
public:
    virtual void init( Render * render ) {}
    virtual void displayReset( Render * render, int x, int y, int width, int height ) {}
    virtual void update( float elapsedTime ) {}
    virtual void display( Render * render ) {}
    virtual void displayLost( Render * render ) {}
    virtual void destroy( Render * render ) {}

};


}