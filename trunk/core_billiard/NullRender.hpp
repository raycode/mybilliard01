#pragma once
namespace my_render {


class NulLRender : IMPLEMENTS_( Render ) {
public:
    virtual void addErrorListener( RenderErrorListener * errorListener ) {}
    virtual void addEventListener( RenderEventListener * eventListener ) {}

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) {}
    virtual void releaseDevice() {}
    virtual bool isDeviceCreated() {}

    virtual bool isWindowed() {}
    virtual void toggleFullScreen() {}

    virtual void force_displayReset() {}

    virtual void* getNativeDevice() {}

    virtual void render() {}

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) {}
    virtual bool beginScene() {}
    virtual void endScene() {}

    virtual void setUpAxis( domUpAxisType up ) {}
    virtual domUpAxisType getUpAxis() {}

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