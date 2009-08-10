#include "DXUT.h"
#include "RenderForDX9.h"

App::App()
: render_( new RenderD3D9Imp() )
, errorListener_( new RenderErrorListenerImp() )
, eventListener_( new RenderEventListenerImp() )
{
}

void App::init() {
    SetDllDirectory( ConstString::dllDirectoryForColladaDOM().c_str() );

    DXUTSetCallbackMsgProc( App::MsgProc, this );
    DXUTSetCallbackKeyboard( App::OnKeyboard, this );
    DXUTSetCallbackFrameMove( App::OnFrameMove, this );

    render_->setScreenWidth( 640 );
    render_->setScreenHeight( 480 );
    render_->setScreenTitle( ConstString::windowTitle() );
    render_->setWindowedMode( true );

    render_->addEventListener( &*eventListener_ );
    render_->addErrorListener( &*errorListener_ );
}

int App::mainLoop() {
    render_->start();
    return DXUTGetExitCode();
}

//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void App::OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    App * const app = (App *) pUserContext;

    // Update the camera's position based on user input 
    app->eventListener_->g_Camera.FrameMove( fElapsedTime );
}



//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT App::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                         void* pUserContext )
{
    App * const app = (App *) pUserContext;

    // Pass messages to dialog resource manager calls so GUI state is updated correctly
    *pbNoFurtherProcessing = app->eventListener_->g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass messages to settings dialog if its active
    if( app->eventListener_->g_SettingsDlg.IsActive() )
    {
        app->eventListener_->g_SettingsDlg.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = app->eventListener_->g_HUD.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = app->eventListener_->g_SampleUI.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
    app->eventListener_->g_Camera.HandleMessages( hWnd, uMsg, wParam, lParam );

    return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void App::OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
}



