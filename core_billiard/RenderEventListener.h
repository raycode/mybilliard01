#pragma once
namespace my_render {


MY_INTERFACE RenderEventListener {
    virtual ~RenderEventListener() {}

    virtual void init( RenderBufferFactory * ) PURE;
    virtual void displayReset( int x, int y, int width, int height ) PURE;
    virtual void update( RenderBufferFactory *, float elapsedTime ) PURE;
    virtual void display( Render * ) PURE;
    virtual void displayLost() PURE;
    virtual void destroy() PURE;

};


}
