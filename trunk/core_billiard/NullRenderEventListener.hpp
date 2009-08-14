#pragma once
namespace my_render {


class NullRenderEventListener : IMPLEMENTS_( RenderEventListener ) {
public:
    virtual void init( RenderBufferFactory * ) OVERRIDE {}
    virtual void displayReset( int x, int y, int width, int height ) OVERRIDE {}
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE {}
    virtual void display( Render * ) OVERRIDE {}
    virtual void displayLost() OVERRIDE {}
    virtual void destroy() OVERRIDE {}

};


}