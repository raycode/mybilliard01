#pragma once
namespace my_render_win32_dx9_imp {


//===================================================
// This class is supposed to work only for DirectX9
//===================================================


class RenderWin32DX9Imp : IMPLEMENTS_( RenderWin32DX9 ) {
public:
    RenderWin32DX9Imp();
    ~RenderWin32DX9Imp();

public: // from RenderWin32DX9
    virtual LPDIRECT3DDEVICE9 getD3D9Device() OVERRIDE;

    virtual void setBackbufferLockable( bool ) OVERRIDE;
    virtual bool isBackbufferLockable() OVERRIDE;

public: // from RenderWin32
    virtual void renderOneFrame() OVERRIDE;

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) OVERRIDE;
    virtual void destroyDevice() OVERRIDE;

    virtual bool isDeviceCreated() OVERRIDE;

    virtual void force_displayReset() OVERRIDE;

    virtual bool isWindowed() OVERRIDE;
    virtual void toggleFullScreen() OVERRIDE;

    virtual void setHWND( HWND ) OVERRIDE;
    virtual HWND getHWND() OVERRIDE;

    virtual void setCursorPosition( int x, int y ) OVERRIDE;
    virtual void showCursor( bool ) OVERRIDE;

    virtual int getFPS() OVERRIDE;

public: // from Render
    virtual void addRenderEventListener( RenderEventListener * eventListener ) OVERRIDE;

    virtual void setClearBackBuffer( NxU32 Color ) OVERRIDE;
    virtual void setClearZBuffer( float z ) OVERRIDE;
    virtual void setClearStencil( NxU32 stencil ) OVERRIDE;
    virtual void clear() OVERRIDE;

    virtual bool beginScene() OVERRIDE;
    virtual void endScene() OVERRIDE;

    virtual void setVertexShader( VertexShader * ) OVERRIDE;
    virtual void setPixelShader( PixelShader * ) OVERRIDE;

    virtual void renderWithEffectShader( EffectShader *, ShaderVariable * technique, RenderEffectShader * callBack ) OVERRIDE;

    virtual void drawPrimitive_POINTLIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;
    virtual void drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;
    virtual void drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;
    virtual void drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;
    virtual void drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;
    virtual void drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_POINTLIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_LINELIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_LINESTRIP(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_TRIANGLELIST(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_TRIANGLESTRIP(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual void drawIndexedPrimitive_TRIANGLEFAN(
        VertexBuffer *, IndexBuffer *,
        int baseVertexIndex, NxU32 minIndex,
        NxU32 startIndex, NxU32 primitiveCount ) OVERRIDE;

    virtual const RenderState * getRenderState() const OVERRIDE;
    virtual RenderState * setRenderState() OVERRIDE;

private: // static members
    static bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext );
    static bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext );

    static HRESULT CALLBACK s_init( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static HRESULT CALLBACK s_displayReset( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext );
    static void CALLBACK s_display( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext );
    static void CALLBACK s_displayLost( void* pUserContext );
    static void CALLBACK s_destroy( void* pUserContext );

private: // buffer factory
    RenderBufferFactoryDX9 * getBufferFactory();
    void setBufferFactory( RenderBufferFactoryDX9Ptr );

private: // render state
    virtual void setRenderState( RenderStatePtr );

private: // draw
    void drawPrimitive( D3DPRIMITIVETYPE primitiveType, VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount );
    void drawIndexedPrimitive( D3DPRIMITIVETYPE primitiveType, VertexBuffer * vb, IndexBuffer * ib,
        int baseVertexIndex, NxU32 minIndex, NxU32 startIndex, NxU32 primitiveCount );

private: // clear
    int clearFlag_;
    NxU32 clearColor_;
    float clearZ_;
    NxU32 clearStencil_;

private:
    RenderEventListener * eventListener_;
    RenderEventListenerNull nullEventListener_;

    RenderBufferFactoryDX9Ptr bufferFactory_;

    RenderStatePtr renderState_;

private: // D3D9 device option
    bool bBackbufferLockable_;

    MY_UNIT_TEST_BACKDOOR;
};


}