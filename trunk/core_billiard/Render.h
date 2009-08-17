#pragma once
namespace my_render {


MY_INTERFACE Render {
    virtual ~Render() {}

    virtual void addRenderEventListener( RenderEventListener * eventListener ) = 0;

    virtual void clear_Color( NxU32 Color ) = 0;
    virtual void clear_Z( float z ) = 0;
    virtual void clear_Stencil( NxU32 stencil ) = 0;
    virtual void clear_Color_Z( NxU32 color, float z ) = 0;
    virtual void clear_Z_Stencil( float z, NxU32 stencil ) = 0;
    virtual void clear_Color_Z_Stencil( NxU32 Color, float z, NxU32 stencil ) = 0;

    virtual bool beginScene() = 0;
    virtual void endScene() = 0;

    virtual void setVertexShader( VertexShader * ) = 0;
    virtual void setPixelShader( PixelShader * ) = 0;

    virtual void renderWithEffectShader( EffectShader *, ShaderVariable * technique, RenderEffectShader * callBack ) = 0;

    virtual void drawPrimitive_POINTLIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;
    virtual void drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;
    virtual void drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;
    virtual void drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;
    virtual void drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;
    virtual void drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_POINTLIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_LINELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_LINESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_TRIANGLELIST( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_TRIANGLESTRIP( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual void drawIndexedPrimitive_TRIANGLEFAN( VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount ) = 0;

    virtual const RenderState * getRenderState() const = 0;
    virtual RenderState * setRenderState() = 0;

};

}