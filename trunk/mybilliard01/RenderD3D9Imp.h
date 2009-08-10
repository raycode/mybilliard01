#pragma once
namespace my_render_d3d9_imp {


class RenderD3D9Imp : IMPLEMENTS_( Render ) {
public:
    RenderD3D9Imp();

public: // from Render
    virtual void addErrorListener( RenderErrorListener * errorListener );
    virtual void addEventListener( RenderEventListener * eventListener );

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight );
    virtual void releaseDevice();
    virtual void* getNativeDevice();

    virtual void clear( int Flags, NxU32 Color, float Z, NxU32 Stencil );
    virtual bool beginScene();
    virtual void endScene();

    virtual void setUpAxis( domUpAxisType up );
    virtual domUpAxisType getUpAxis();

    virtual void pushMatrix();
    virtual void popMatrix();
    virtual void loadIdentity();
    virtual void multMatrix( NxMat34 );

    virtual void drawPrimitive(
        EPrimitiveType primitiveType,
        NxU32 startVertex,
        NxU32 primitiveCount );

    virtual void drawIndexedPrimitive(
        EPrimitiveType primitiveType,
        int baseVertexIndex,
        NxU32 minIndex,
        NxU32 numVertices,
        NxU32 startIndex,
        NxU32 primitiveCount );

public: // render state
    virtual void getRenderState( ERenderStateType State, NxU32 * pValue );
    virtual void setRenderState( ERenderStateType State, NxU32 Value );

public: // static members
    static bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
    static bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );

    static HRESULT CALLBACK s_init( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static HRESULT CALLBACK s_displayReset( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static void CALLBACK s_display( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static void CALLBACK s_displayLost( void* pUserContext );


private:
    domUpAxisType upAxis_;

    RenderErrorListener * errorListener_;
    RenderEventListener * eventListener_;

    NullRenderErrorListener nullErrorListener_;
    NullRenderEventListener nullEventListener_;

private:
    IDirect3DDevice9 * d3dDevice_;
};

}