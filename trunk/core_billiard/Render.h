#pragma once
namespace my_render {


MY_INTERFACE Render {
    virtual ~Render() {}

    virtual void addRenderEventListener( RenderEventListener * eventListener ) PURE;

    virtual void clear_Color( NxU32 Color ) PURE;
    virtual void clear_Z( float z ) PURE;
    virtual void clear_Stencil( NxU32 stencil ) PURE;
    virtual void clear_Color_Z( NxU32 color, float z ) PURE;
    virtual void clear_Z_Stencil( float z, NxU32 stencil ) PURE;
    virtual void clear_Color_Z_Stencil( NxU32 Color, float z, NxU32 stencil ) PURE;

    virtual bool beginScene() PURE;
    virtual void endScene() PURE;

    virtual const RenderState * getRenderState() const PURE;
    virtual RenderState * setRenderState() PURE;

    virtual void setRenderTarget( Texture * ) PURE;
    virtual void unsetRenderTarget() PURE;

};

}