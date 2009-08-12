#pragma once
namespace my_render {


class NullRender : IMPLEMENTS_( Render ) {
public:
    virtual void render() OVERRIDE {}
    virtual void addRenderEventListener( RenderEventListener * eventListener ) OVERRIDE {}

    virtual void setUpAxis( domUpAxisType up ) OVERRIDE {}
    virtual domUpAxisType getUpAxis() OVERRIDE { return UPAXISTYPE_Y_UP; }

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) OVERRIDE {}
    virtual bool beginScene() OVERRIDE { return false; }
    virtual void endScene() OVERRIDE {}

    virtual void pushMatrix() OVERRIDE {}
    virtual void popMatrix() OVERRIDE {}
    virtual void loadIdentity() OVERRIDE {}
    virtual void multMatrix( NxMat34 ) OVERRIDE {}

    virtual void drawPrimitive(
        EPrimitiveType primitiveType,
        NxU32 startVertex,
        NxU32 primitiveCount ) OVERRIDE {}

    virtual void drawIndexedPrimitive(
        EPrimitiveType primitiveType,
        int baseVertexIndex,
        NxU32 minIndex,
        NxU32 numVertices,
        NxU32 startIndex,
        NxU32 primitiveCount ) OVERRIDE {}

    virtual void getRenderState( ERenderStateType State, NxU32 * pValue ) OVERRIDE {}
    virtual void setRenderState( ERenderStateType State, NxU32 Value ) OVERRIDE {}
};


}