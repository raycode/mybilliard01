#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"

void DXUTCheckForWindowSizeChange();
void DXUTCheckForWindowChangingMonitors();
void WINAPI DXUTDisplaySwitchingToREFWarning( DXUTDeviceVersion ver );

namespace my_render_win32_dx9_imp {

#ifdef DEBUG
#define DEBUG_VS   // Uncomment this line to debug D3D9 vertex shaders 
#define DEBUG_PS   // Uncomment this line to debug D3D9 pixel shaders 
#endif

RenderWin32DX9Imp::RenderWin32DX9Imp()
: bBackbufferLockable_( false )
, bufferFactory_( RenderBufferFactoryDX9Ptr( new RenderBufferFactoryDX9Null() ) )
, renderState_( RenderStatePtr( new RenderStateNull() ) )
{
    eventListener_ =  &nullEventListener_;

    DXUTInit( false, false, NULL ); // Parse the command line, show msgboxes on error, no extra command line params
    DXUTSetCursorSettings( true, true );
    DXUTSetCallbackD3D9DeviceAcceptable( &RenderWin32DX9Imp::IsD3D9DeviceAcceptable, this );
    DXUTSetCallbackDeviceChanging( &RenderWin32DX9Imp::ModifyDeviceSettings, this );
    //DXUTSetCallbackMsgProc( ApplicationWin32Imp::MsgProc );

    DXUTSetCallbackD3D9DeviceCreated( &RenderWin32DX9Imp::s_init, this );
    DXUTSetCallbackD3D9DeviceReset( &RenderWin32DX9Imp::s_displayReset, this );
    DXUTSetCallbackD3D9FrameRender( &RenderWin32DX9Imp::s_display, this );
    DXUTSetCallbackD3D9DeviceLost( &RenderWin32DX9Imp::s_displayLost, this );
    DXUTSetCallbackD3D9DeviceDestroyed( &RenderWin32DX9Imp::s_destroy, this );
}

RenderWin32DX9Imp::~RenderWin32DX9Imp() {
    if( isDeviceCreated() )
        destroyDevice();
}

void RenderWin32DX9Imp::destroyDevice()
{
    DXUTShutdown();
    DXUTResetFrameworkState();
}

void RenderWin32DX9Imp::renderOneFrame() {
    DXUTRender3DEnvironment();
}

bool RenderWin32DX9Imp::createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) {
    const HRESULT hr = DXUTCreateDevice( bWindowed, nSuggestedWidth, nSuggestedHeight );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"RenderWin32DX9Imp::createDevice", hr );
        return false;
    }
    return true;
}

bool RenderWin32DX9Imp::isDeviceCreated() {
    return NULL != getD3D9Device();
}

void RenderWin32DX9Imp::setHWND( HWND hWnd ) {
    DXUTSetWindow( hWnd, hWnd, hWnd, false );
}

HWND RenderWin32DX9Imp::getHWND() {
    return DXUTGetHWND();
}

int RenderWin32DX9Imp::getFPS() {
    return (int) DXUTGetFPS();
}

void RenderWin32DX9Imp::force_displayReset() {
    DXUTCheckForWindowSizeChange();
    DXUTCheckForWindowChangingMonitors();
}

IDirect3DDevice9* RenderWin32DX9Imp::getD3D9Device() {
    return DXUTGetD3D9Device();
}

bool RenderWin32DX9Imp::isWindowed() {
    return DXUTIsWindowed();
}

void RenderWin32DX9Imp::toggleFullScreen()
{
    DXUTToggleFullScreen();
}

void RenderWin32DX9Imp::setCursorPosition( int x, int y ) {
    getD3D9Device()->SetCursorPosition( x, y, 0 );
}

void RenderWin32DX9Imp::showCursor( bool val ) {
    getD3D9Device()->ShowCursor( val );
}

RenderBufferFactoryDX9 * RenderWin32DX9Imp::getBufferFactory() {
    return bufferFactory_.get();
}

void RenderWin32DX9Imp::setBufferFactory( RenderBufferFactoryDX9Ptr factory ) {
    bufferFactory_ = factory;
}

void RenderWin32DX9Imp::setBackbufferLockable( bool val ) {
    bBackbufferLockable_ = val;
}

bool RenderWin32DX9Imp::isBackbufferLockable() {
    return bBackbufferLockable_;
}


void RenderWin32DX9Imp::addRenderEventListener( RenderEventListener * eventListener ) {
    eventListener_ = ( ( NULL == eventListener ) ? &nullEventListener_ : eventListener );
}

HRESULT RenderWin32DX9Imp::s_init( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext ) {
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_init()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    render->setBufferFactory( RenderBufferFactoryDX9Ptr( new RenderBufferFactoryDX9Imp( pd3dDevice ) ) );
    render->setRenderState( RenderStatePtr( new RenderStateDX9Imp( pd3dDevice ) ) );

    render->getBufferFactory()->init();
    render->eventListener_->init();

    return S_OK;
}

HRESULT RenderWin32DX9Imp::s_displayReset( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_displayReset()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;
    const RECT rc = DXUTGetWindowClientRect();

    render->getBufferFactory()->displayReset( NULL, rc.left, rc.top, pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );
    render->eventListener_->displayReset( render->getBufferFactory(), rc.left, rc.top, pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height );

    return S_OK;
}

void RenderWin32DX9Imp::s_display( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext ) {
    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;

    render->eventListener_->update( render->getBufferFactory(), fElapsedTime );
    render->getBufferFactory()->update( NULL, fElapsedTime );

    render->eventListener_->display( render );
}

void RenderWin32DX9Imp::s_displayLost( void* pUserContext ) {
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_displayLost()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;

    render->eventListener_->displayLost();
    render->getBufferFactory()->displayLost();
}

void RenderWin32DX9Imp::s_destroy( void* pUserContext ) {
    ::OutputDebugStr( L"RenderWin32DX9Imp::s_destroy()\n" );

    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;

    render->eventListener_->destroy();
    render->getBufferFactory()->destroy();

    render->setRenderState( RenderStatePtr( new RenderStateNull() ) );
    render->setBufferFactory( RenderBufferFactoryDX9Ptr( new RenderBufferFactoryDX9Null() ) );
}


//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool RenderWin32DX9Imp::IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat,
                                     D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Skip backBuffer formats that don't support alpha blending
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
    RenderWin32DX9Imp * const render = (RenderWin32DX9Imp*) pUserContext;

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

        if( render->isBackbufferLockable() )
            pDeviceSettings->d3d9.pp.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

#ifdef DEBUG_VS
        // Debugging vertex shaders requires either REF or software vertex processing 
        // and debugging pixel shaders requires REF.  
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
    static bool s_bFirstTime = false; // true;
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

bool RenderWin32DX9Imp::beginScene() {
    return D3D_OK == getD3D9Device()->BeginScene();
}

void RenderWin32DX9Imp::endScene() {
    getD3D9Device()->EndScene();
}

void RenderWin32DX9Imp::clear_Color( NxU32 Color ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_TARGET, Color, 0.f, 0 );
}

void RenderWin32DX9Imp::clear_Z( float z ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_ZBUFFER, 0, z, 0 );
}

void RenderWin32DX9Imp::clear_Stencil( NxU32 stencil ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_STENCIL, 0, 0.f, stencil );
}

void RenderWin32DX9Imp::clear_Color_Z( NxU32 color, float z ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, z, 0 );
}

void RenderWin32DX9Imp::clear_Z_Stencil( float z, NxU32 stencil ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, z, stencil );
}

void RenderWin32DX9Imp::clear_Color_Z_Stencil( NxU32 Color, float z, NxU32 stencil ) {
    getD3D9Device()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, Color, z, stencil );
}


void RenderWin32DX9Imp::setRenderState( RenderStatePtr renderState )
{
    renderState_ = renderState;
}

const RenderState * RenderWin32DX9Imp::getRenderState() const
{
    return renderState_.get();
}

RenderState * RenderWin32DX9Imp::setRenderState()
{
    return renderState_.get();
}

SurfaceDX9 * RenderWin32DX9Imp::acquireBackBuffer( size_t whichBackBuffer )
{
    IDirect3DSurface9 * newDXSurface;
    const HRESULT hr = getD3D9Device()->GetBackBuffer( 0, whichBackBuffer, D3DBACKBUFFER_TYPE_MONO, &newDXSurface );
    RETURN_NULL_IF_FAILED( hr, L"RenderWin32DX9Imp::acquireBackBuffer" );

    SurfaceDX9Ptr newSurface = SurfaceDX9Ptr( new SurfaceDX9Imp( IDirect3DSurface9Ptr( newDXSurface, ComReleaser< IDirect3DSurface9 >() ) ) );
    backBuffers_.push_back( newSurface );
    return newSurface.get();
}

bool RenderWin32DX9Imp::releaseBackBuffer( SurfaceDX9 * backBuffer ) {
    return remove_only_one_pointer( backBuffers_, backBuffer );
}


}
