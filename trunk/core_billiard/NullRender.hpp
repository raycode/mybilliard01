#pragma once
namespace my_render {


class NullRender : IMPLEMENTS_( Render ) {
public:
    virtual void addErrorListener( RenderErrorListener * errorListener ) {}
    virtual void addEventListener( RenderEventListener * eventListener ) {}

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) { return false; }
    virtual void releaseDevice() {}
    virtual bool isDeviceCreated() { return false; }

    virtual bool isWindowed() { return true; }
    virtual void toggleFullScreen() {}

    virtual void force_displayReset() {}

    virtual void* getNativeDevice() { return NULL; }

    virtual void render() {}

    virtual void setCursorPosition( int x, int y ) {}
    virtual void showCursor( bool ) {}

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) {}
    virtual bool beginScene() { return false; }
    virtual void endScene() {}

    virtual void setUpAxis( domUpAxisType up ) {}
    virtual domUpAxisType getUpAxis() { return UPAXISTYPE_Y_UP; }

    virtual void pushMatrix() {}
    virtual void popMatrix() {}
    virtual void loadIdentity() {}
    virtual void multMatrix( NxMat34 ) {}

    virtual void drawPrimitive(
        EPrimitiveType primitiveType,
        NxU32 startVertex,
        NxU32 primitiveCount ) {}

    virtual void drawIndexedPrimitive(
        EPrimitiveType primitiveType,
        int baseVertexIndex,
        NxU32 minIndex,
        NxU32 numVertices,
        NxU32 startIndex,
        NxU32 primitiveCount ) {}

    virtual void getRenderState( ERenderStateType State, NxU32 * pValue ) {}
    virtual void setRenderState( ERenderStateType State, NxU32 Value ) {}
};


}