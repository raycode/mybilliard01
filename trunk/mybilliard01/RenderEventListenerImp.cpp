#include "DXUT.h"
#include "RenderForDX9.h"


void RenderEventListenerImp::display( Render * render ) {
}

void RenderEventListenerImp::displayChanged( Render * render, bool modeChanged, bool deviceChanged) {
}

RenderEventListenerImp::RenderEventListenerImp()
: g_pTxtHelper( NULL )
, g_pFont9( NULL )
, g_pSprite9( NULL )
, g_pEffect9( NULL )

{
}

void RenderEventListenerImp::init( Render * render ) {

    IDirect3DDevice9 * const pd3dDevice = (IDirect3DDevice9*) render->getNativeDevice();

    HRESULT hr;

    V( g_DialogResourceManager.OnD3D9CreateDevice( pd3dDevice ) );
    V( g_SettingsDlg.OnD3D9CreateDevice( pd3dDevice ) );

    V( D3DXCreateFont( pd3dDevice, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"Arial", &g_pFont9 ) );

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
        NULL, &g_pEffect9, NULL ) );

    // Setup the camera's view parameters
    D3DXVECTOR3 vecEye( 0.0f, 0.0f, -5.0f );
    D3DXVECTOR3 vecAt ( 0.0f, 0.0f, -0.0f );
    g_Camera.SetViewParams( &vecEye, &vecAt );
}

void RenderEventListenerImp::reshape( Render * redner, int x, int y, int width, int height ) {

}


