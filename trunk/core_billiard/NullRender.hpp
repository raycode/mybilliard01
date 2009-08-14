#pragma once
namespace my_render {


class NullRender : IMPLEMENTS_( Render ) {
public:
    virtual void addRenderEventListener( RenderEventListener * eventListener ) OVERRIDE {}

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) OVERRIDE {}
    virtual bool beginScene() OVERRIDE { return false; }
    virtual void endScene() OVERRIDE {}

    virtual void drawPrimitive_POINTLIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}
    virtual void drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_POINTLIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_LINELIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_LINESTRIP(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLELIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLESTRIP(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive_TRIANGLEFAN(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE {}

    virtual void getRenderState( ERenderStateType State, NxU32 * pValue ) OVERRIDE {}
    virtual void setRenderState( ERenderStateType State, NxU32 Value ) OVERRIDE {}
};


}