#pragma once
namespace my_render {


MY_INTERFACE RenderEventListener {
    virtual ~RenderEventListener() {}

    virtual void init( RenderBufferFactory * ) = 0;
    virtual void displayReset( int x, int y, int width, int height ) = 0;
    virtual void update( RenderBufferFactory *, float elapsedTime ) = 0;
    virtual void display( Render * ) = 0;
    virtual void displayLost() = 0;
    virtual void destroy() = 0;

};


}
