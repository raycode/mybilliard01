#pragma once
namespace my_render {


NULL_OBJECT( Render ) {

    virtual void addRenderEventListener( RenderEventListener * eventListener ) OVERRIDE {}

    virtual void setClearBackBuffer( NxU32 Color ) OVERRIDE {}
    virtual void setClearZBuffer( float z ) OVERRIDE {}
    virtual void setClearStencil( NxU32 stencil ) OVERRIDE {}
    virtual void clear() OVERRIDE {}

    virtual bool beginScene() OVERRIDE { return false; }
    virtual void endScene() OVERRIDE {}

    virtual void setVertexShader( VertexShader * ) OVERRIDE {}
    virtual void setPixelShader( PixelShader * ) OVERRIDE {}
    virtual void renderWithEffectShader( EffectShader *, ShaderVariable * technique, RenderEffectShader * callBack ) OVERRIDE {}

    virtual void drawPrimitive_POINTLIST( VertexBuffer *, NxU32 startVertex, NxU32 privmitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_POINTLIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_LINELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_LINESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLEFAN( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual const RenderState * getRenderState() const OVERRIDE { return & nullRenderState_; }
    virtual RenderState * setRenderState() OVERRIDE { return & nullRenderState_; }

private:
    RenderStateNull nullRenderState_;
};


}