#pragma once
namespace my_render {


NULL_OBJECT( Render ) {

    virtual void addRenderEventListener( RenderEventListener * eventListener ) OVERRIDE {}

    virtual void clear_Color( NxU32 Color ) OVERRIDE {}
    virtual void clear_Z( float z ) OVERRIDE {}
    virtual void clear_Stencil( NxU32 stencil ) OVERRIDE {}
    virtual void clear_Color_Z( NxU32 color, float z ) OVERRIDE {}
    virtual void clear_Z_Stencil( float z, NxU32 stencil ) OVERRIDE {}
    virtual void clear_Color_Z_Stencil( NxU32 Color, float z, NxU32 stencil ) OVERRIDE {}

    virtual bool beginScene() OVERRIDE { return false; }
    virtual void endScene() OVERRIDE {}

    virtual const RenderState * getRenderState() const OVERRIDE { return &nullRenderState_; }
    virtual RenderState * setRenderState() OVERRIDE { return &nullRenderState_; }

    virtual size_t getRenderTargetWidth() OVERRIDE { return 0; }
    virtual size_t getRenderTargetHeight() OVERRIDE { return 0; }

private:
    RenderStateNull nullRenderState_;
};


}