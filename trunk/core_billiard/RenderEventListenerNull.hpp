#pragma once
namespace my_render {


NULL_OBJECT( RenderEventListener ) {

    virtual void init() OVERRIDE {}
    virtual void displayReset( RenderBufferFactory *, int x, int y, int width, int height ) OVERRIDE {}
    virtual void update( RenderBufferFactory *, float elapsedTime ) OVERRIDE {}
    virtual void display( Render * ) OVERRIDE {}
    virtual void displayLost() OVERRIDE {}
    virtual void destroy() OVERRIDE {}

};


}