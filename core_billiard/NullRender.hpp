#pragma once
namespace my_render {


class NullRender : IMPLEMENTS_( Render ) {
public:
    virtual void render() OVERRIDE {}
    virtual void addEventListener( RenderEventListener * eventListener ) OVERRIDE {}

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) OVERRIDE { return false; }
    virtual void releaseDevice() OVERRIDE {}
    virtual void* getNativeDevice() OVERRIDE { return NULL; }
    virtual bool isDeviceCreated() OVERRIDE { return false; }

    virtual void force_displayReset() OVERRIDE {}

    virtual bool isWindowed() OVERRIDE { return true; }
    virtual void toggleFullScreen() OVERRIDE {}

    virtual void setUpAxis( domUpAxisType up ) OVERRIDE {}
    virtual domUpAxisType getUpAxis() OVERRIDE { return UPAXISTYPE_Y_UP; }

    virtual void setCursorPosition( int x, int y ) OVERRIDE {}
    virtual void showCursor( bool ) OVERRIDE {}

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