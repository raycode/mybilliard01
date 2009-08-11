#include "DXUT.h"
#include "my_app.h"

//--------------------------------------------------------------------------------------
// UI control IDs
//--------------------------------------------------------------------------------------
#define IDC_TOGGLEFULLSCREEN    1
#define IDC_TOGGLEREF           2
#define IDC_CHANGEDEVICE        3


void RenderEventListenerImp::initDXUT( Render * render )
{
    settingsDlg_.Init( &dialogResourceManager_ );
    hud_.Init( &dialogResourceManager_ );
    sampleUI_.Init( &dialogResourceManager_ );

    hud_.SetCallback( OnGUIEvent, this );
    int iY = 10;
    hud_.AddButton( IDC_TOGGLEFULLSCREEN, L"Toggle full screen", 35, iY, 125, 22 );
    hud_.AddButton( IDC_TOGGLEREF, L"Toggle REF (F3)", 35, iY += 24, 125, 22, VK_F3 );
    hud_.AddButton( IDC_CHANGEDEVICE, L"Change device (F2)", 35, iY += 24, 125, 22, VK_F2 );

    sampleUI_.SetCallback( OnGUIEvent );


    IDirect3DDevice9 * const pd3dDevice = (IDirect3DDevice9*) render->getNativeDevice();

    HRESULT hr;
    V( dialogResourceManager_.OnD3D9CreateDevice( pd3dDevice ) );
    V( settingsDlg_.OnD3D9CreateDevice( pd3dDevice ) );
    V( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"Arial", &font9_ ) );

    // Read the D3DX effect file
    WCHAR str[MAX_PATH];
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

#ifdef DEBUG_VS
    dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
    dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

    V( DXUTFindDXSDKMediaFileCch( str, MAX_PATH, ConstString::effectFilename().c_str() ) );
    V( D3DXCreateEffectFromFile( pd3dDevice, str, NULL, NULL, dwShaderFlags,
        NULL, &effect9_, NULL ) );

    // Setup the camera's view parameters
    D3DXVECTOR3 vecEye( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vecAt ( 0.0f, 0.0f, -0.0f );
    camera_.SetViewParams( &vecEye, &vecAt );
}

void RenderEventListenerImp::destroyDXUT()
{
    dialogResourceManager_.OnD3D9DestroyDevice();
    settingsDlg_.OnD3D9DestroyDevice();
    SAFE_RELEASE( effect9_ );
    SAFE_RELEASE( font9_ );
}

//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
void RenderEventListenerImp::displayResetDXUT( Render * render, int width, int height )
{
    IDirect3DDevice9 * const pd3dDevice = (IDirect3DDevice9*) render->getNativeDevice();

    HRESULT hr;
    V( dialogResourceManager_.OnD3D9ResetDevice() );
    V( settingsDlg_.OnD3D9ResetDevice() );

    if( font9_ ) font9_->OnResetDevice();
    if( effect9_ ) effect9_->OnResetDevice();

    V( D3DXCreateSprite( pd3dDevice, &sprite9_ ) );
    textHelper_ = new CDXUTTextHelper( font9_, sprite9_, NULL, NULL, 15 );

    // Setup the camera's projection parameters
    float fAspectRatio = width / ( float ) height;
    camera_.SetProjParams( D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f );
    camera_.SetWindow( width, height );

    hud_.SetLocation( width - 170, 0 );
    hud_.SetSize( 170, 170 );
    sampleUI_.SetLocation( width - 170, height - 350 );
    sampleUI_.SetSize( 170, 300 );
}

//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the displayReset callback 
//--------------------------------------------------------------------------------------
void RenderEventListenerImp::displayLostDXUT() {
    dialogResourceManager_.OnD3D9LostDevice();
    settingsDlg_.OnD3D9LostDevice();
    if( font9_ ) font9_->OnLostDevice();
    if( effect9_ ) effect9_->OnLostDevice();
    SAFE_RELEASE( sprite9_ );
    SAFE_DELETE( textHelper_ );
}


void RenderEventListenerImp::displayDXUT() {
    const float elapsedTime = 1.f/60.f; // This should be eliminated in future.

    HRESULT hr;
    D3DXMATRIXA16 mWorld;
    D3DXMATRIXA16 mView;
    D3DXMATRIXA16 mProj;
    D3DXMATRIXA16 mWorldViewProjection;

    if( settingsDlg_.IsActive() )
    {
        settingsDlg_.OnRender( elapsedTime );
        return;
    }

    // Get the projection & view matrix from the camera class
    mWorld = *camera_.GetWorldMatrix();
    mProj = *camera_.GetProjMatrix();
    mView = *camera_.GetViewMatrix();

    mWorldViewProjection = mWorld * mView * mProj;

    // Update the effect's variables.  Instead of using strings, it would 
    // be more efficient to cache a handle to the parameter by calling 
    // ID3DXEffect::GetParameterByName
    V( effect9_->SetMatrix( "g_mWorldViewProjection", &mWorldViewProjection ) );
    V( effect9_->SetMatrix( "g_mWorld", &mWorld ) );
    //V( g_pEffect9->SetFloat( "g_fTime", ( float )fTime ) );

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"HUD / Stats" ); // These events are to help PIX identify what the code is doing
    displayDXUTText();
    V( hud_.OnRender( elapsedTime ) );
    V( sampleUI_.OnRender( elapsedTime ) );
    DXUT_EndPerfEvent();


}

//--------------------------------------------------------------------------------------
// Render the help and statistics text. This function uses the ID3DXFont interface for 
// efficient text rendering.
//--------------------------------------------------------------------------------------
void RenderEventListenerImp::displayDXUTText()
{
    textHelper_->Begin();
    textHelper_->SetInsertionPos( 5, 5 );
    textHelper_->SetForegroundColor( D3DXCOLOR( 1.0f, 1.0f, 0.0f, 1.0f ) );
    textHelper_->DrawTextLine( DXUTGetFrameStats( DXUTIsVsyncEnabled() ) );
    textHelper_->DrawTextLine( DXUTGetDeviceStats() );
    textHelper_->End();
}


//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void RenderEventListenerImp::OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
    RenderEventListenerImp * const eventListener = (RenderEventListenerImp*) pUserContext;

    switch( nControlID )
    {
    case IDC_TOGGLEFULLSCREEN:
        DXUTToggleFullScreen();
        break;

    case IDC_TOGGLEREF:
        DXUTToggleREF();
        break;

    case IDC_CHANGEDEVICE:
        eventListener->settingsDlg_.SetActive( !eventListener->settingsDlg_.IsActive() );
        break;
    }
}

