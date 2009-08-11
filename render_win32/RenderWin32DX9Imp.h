#pragma once
namespace my_render_win32_dx9_imp {


//===================================================
// This class is supposed to work only for DirectX9
//===================================================


class RenderWin32DX9Imp : IMPLEMENTS_( RenderWin32DX9 ) {
public:
    RenderWin32DX9Imp();

public: // from RenderWin32
    virtual void setHWND( HWND );

public: // from Render
    virtual void addErrorListener( RenderErrorListener * errorListener );
    virtual void addEventListener( RenderEventListener * eventListener );

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight );
    virtual void releaseDevice();
    virtual bool isDeviceCreated();

    virtual bool isWindowed();
    virtual void toggleFullScreen();

    virtual void* getNativeDevice();

    virtual void force_displayReset();

    virtual void render();

    virtual void setCursorPosition( int x, int y );
    virtual void showCursor( bool );

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
    HWND hWnd_;
    IDirect3DDevice9 * d3dDevice_;
};

}