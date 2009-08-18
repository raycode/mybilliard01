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

    virtual void setVertexShader( VertexShader * ) PURE;
    virtual void setPixelShader( PixelShader * ) PURE;

    virtual void renderWithEffectShader( EffectShader *, ShaderVariable * technique, RenderEffectShader * callBack ) PURE;

    virtual void drawPrimitive_POINTLIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;
    virtual void drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;
    virtual void drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;
    virtual void drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;
    virtual void drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;
    virtual void drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_POINTLIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_LINELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_LINESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_TRIANGLELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_TRIANGLESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual void drawIndexedPrimitive_TRIANGLEFAN( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) PURE;

    virtual const RenderState * getRenderState() const = 0;
    virtual RenderState * setRenderState() PURE;

};

}