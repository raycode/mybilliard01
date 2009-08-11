#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"

void DXUTCheckForWindowSizeChange();
void DXUTCheckForWindowChangingMonitors();
HRESULT DXUTChangeDevice( DXUTDeviceSettings* pNewDeviceSettings,
                         IDirect3DDevice9* pd3d9DeviceFromApp, ID3D10Device* pd3d10DeviceFromApp,
                         bool bForceRecreate, bool bClipWindowToSingleAdapter );

namespace my_render_win32_dx9_imp {

//#define DEBUG_VS   // Uncomment this line to debug D3D9 vertex shaders 
//#define DEBUG_PS   // Uncomment this line to debug D3D9 pixel shaders 

RenderWin32DX9Imp::RenderWin32DX9Imp()
: upAxis_( UPAXISTYPE_Y_UP )
, d3dDevice_( NULL )
{
    errorListener_ = &nullErrorListener_;
    eventListener_ = &nullEventListener_;

    // DXUT implementation doesn't allow more than one D3D device at time, which is bad.
    DXUTInit( true, true, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true );
    DXUTSetCallbackD3D9DeviceAcceptable( &RenderWin32DX9Imp::IsD3D9DeviceAcceptable );
    DXUTSetCallbackDeviceChanging( &RenderWin32DX9Imp::ModifyDeviceSettings );

    DXUTSetCallbackD3D9DeviceCreated( &RenderWin32DX9Imp::s_init, this );
    DXUTSetCallbackD3D9DeviceReset( &RenderWin32DX9Imp::s_displayReset, this );
    DXUTSetCallbackD3D9FrameRender( &RenderWin32DX9Imp::s_display, this );
    DXUTSetCallbackD3D9DeviceLost( &RenderWin32DX9Imp::s_displayLost, this );
}

void RenderWin32DX9Imp::render() {
    DXUTRender3DEnvironment();
}

bool RenderWin32DX9Imp::createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) {
    //GetDXUTState().SetWindowCreated( true );
    //GetDXUTState().SetHWNDFocus( hWnd );
    //GetDXUTState().SetHWNDDeviceFullScreen( hWnd );
    //GetDXUTState().SetHWNDDeviceWindowed( hWnd );
    return S_OK == DXUTCreateDevice( bWindowed, nSuggestedWidth, nSuggestedHeight );
}

void RenderWin32DX9Imp::releaseDevice()
{
    if( false == isDeviceCreated() ) return;

    DXUTSetCallbackD3D9DeviceLost( NULL );
    s_displayLost( this );

    ::OutputDebugStr( L"RenderEventListener::destroy()\n" );
    eventListener_->destroy( this );

    d3dDevice_ = NULL;
}

void RenderWin32DX9Imp::setHWND( HWND hWnd ) {
    hWnd_ = hWnd;
}

bool RenderWin32DX9Imp::isDeviceCreated() {
    return NULL != d3dDevice_;
}

void RenderWin32DX9Imp::force_displayReset() {
    DXUTCheckForWindowSizeChange();
    DXUTCheckForWindowChangingMonitors();
}

void* RenderWin32DX9Imp::getNativeDevice() {
    return d3dDevice_;
}

bool RenderWin32DX9Imp::isWindowed() {
    return DXUTIsWindowed();
}

void RenderWin32DX9Imp::toggleFullScreen()
{
    DXUTToggleFullScreen();
}

void RenderWin32DX9Imp::setCursorPosition( int x, int y ) {
    d3dDevice_->SetCursorPosition( x, y, 0 );
}

void RenderWin32DX9Imp::showCursor( bool val ) {
    d3dDevice_->ShowCursor( val );
}

void RenderWin32DX9Imp::setUpAxis( domUpAxisType up ) {
    upAxis_ = up;
}

domUpAxisType RenderWin32DX9Imp::getUpAxis() {
    return upAxis_;
}

void RenderWin32DX9Imp::addErrorListener( RenderErrorListener * errorListener ) {
    errorListener_ = errorListener;
}

void RenderWin32DX9Imp::addEventListener( RenderEventListener * eventListener ) {
    eventListener_ = eventListener;
}

HRESULT RenderWin32DX9Imp::s_init( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext ) {
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_init()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    render->d3dDevice_ = pd3dDevice;

    render->eventListener_->init( render );
    return S_OK;
}

void RenderWin32DX9Imp::s_display( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext ) {
    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    render->eventListener_->update( fElapsedTime );
    render->eventListener_->display( render );
}

HRESULT RenderWin32DX9Imp::s_displayReset( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_displayReset()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    const RECT rc = DXUTGetWindowClientRect();

    render->eventListener_->displayReset( render, rc.left, rc.top, pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
    return 11;
}

void RenderWin32DX9Imp::s_displayLost( void* pUserContext ) {
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_displayLost()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    render->eventListener_->displayLost( render );
}

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool RenderWin32DX9Imp::IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
                                     D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
        AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
        D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    // No fallback defined by this app, so reject any device that 
    // doesn't support at least ps2.0
    if( pCaps->PixelShaderVersion < D3DPS_VERSION( 2, 0 ) )
        return false;
    if( pCaps->VertexShaderVersion < D3DVS_VERSION( 1, 1 ) )
        return false;

    return true;
}

//--------------------------------------------------------------------------------------
// Called right before creating a D3D9 or D3D10 device, allowing the app to modify the device settings as needed
//--------------------------------------------------------------------------------------
bool RenderWin32DX9Imp::ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
    if( pDeviceSettings->ver == DXUT_D3D9_DEVICE )
    {
        IDirect3D9* pD3D = DXUTGetD3D9Object();
        D3DCAPS9 Caps;
        pD3D->GetDeviceCaps( pDeviceSettings->d3d9.AdapterOrdinal, pDeviceSettings->d3d9.DeviceType, &Caps );

        // If device doesn't support HW T&L or doesn't support 1.1 vertex shaders in HW 
        // then switch to SWVP.
        if( ( Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) == 0 ||
            Caps.VertexShaderVersion < D3DVS_VERSION( 1, 1 ) )
        {
            pDeviceSettings->d3d9.BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }

        // Debugging vertex shaders requires either REF or software vertex processing 
        // and debugging pixel shaders requires REF.  
#ifdef DEBUG_VS
        if( pDeviceSettings->d3d9.DeviceType != D3DDEVTYPE_REF )
        {
            pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_HARDWARE_VERTEXPROCESSING;
            pDeviceSettings->d3d9.BehaviorFlags &= ~D3DCREATE_PUREDEVICE;
            pDeviceSettings->d3d9.BehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
        }
#endif
#ifdef DEBUG_PS
        pDeviceSettings->d3d9.DeviceType = D3DDEVTYPE_REF;
#endif
    }

    // For the first device created if its a REF device, optionally display a warning dialog box
    static bool s_bFirstTime = true;
    if( s_bFirstTime )
    {
        s_bFirstTime = false;
        if( ( DXUT_D3D9_DEVICE == pDeviceSettings->ver && pDeviceSettings->d3d9.DeviceType == D3DDEVTYPE_REF ) ||
            ( DXUT_D3D10_DEVICE == pDeviceSettings->ver &&
            pDeviceSettings->d3d10.DriverType == D3D10_DRIVER_TYPE_REFERENCE ) )
            DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
    }

    return true;
}

void RenderWin32DX9Imp::pushMatrix() {

}

void RenderWin32DX9Imp::popMatrix() {

}

void RenderWin32DX9Imp::loadIdentity() {

}

void RenderWin32DX9Imp::multMatrix( NxMat34 ) {

}

bool RenderWin32DX9Imp::beginScene() {
    return D3D_OK == d3dDevice_->BeginScene();
}

void RenderWin32DX9Imp::endScene() {
    d3dDevice_->EndScene();
}

void RenderWin32DX9Imp::clear( int Flags, NxU32 Color, float Z, NxU32 Stencil ) {
    d3dDevice_->Clear( 0, NULL, Flags, Color, Z, Stencil );
}

void RenderWin32DX9Imp::drawPrimitive(
    EPrimitiveType primitiveType,
    NxU32 startVertex,
    NxU32 primitiveCount )
{
}

void RenderWin32DX9Imp::drawIndexedPrimitive(
    EPrimitiveType primitiveType,
    int baseVertexIndex,
    NxU32 minIndex,
    NxU32 numVertices,
    NxU32 startIndex,
    NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::getRenderState( ERenderStateType State, NxU32 * pValue ) {

}

void RenderWin32DX9Imp::setRenderState( ERenderStateType State, NxU32 Value ) {

}

}
