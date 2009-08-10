#include "DXUT.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {


void ApplicationWin32Imp::openWindow() {
    if( S_OK != DXUTCreateWindow( getScreenTitle().c_str() ) ) // this should also work for OpenGL.
        throw exception();

    if( false == render_->createDevice( isWindowedMode(), getScreenWidth(), getScreenHeight() ) )
         throw exception();

    mainLoop();

    render_->releaseDevice();
}

void ApplicationWin32Imp::setRender( Render * render ) {
    render_ = render;
}

void ApplicationWin32Imp::setScreenWidth( int width ) {
    width_ = width;
}

void ApplicationWin32Imp::setScreenHeight( int height ) {
    height_ = height;
}

void ApplicationWin32Imp::setWindowedMode( bool mode ) {
    bWindowedMode_ = mode;
}

void ApplicationWin32Imp::setScreenTitle( wstring title ) {
    title_ = title;
}

void ApplicationWin32Imp::addKeyboardListener( KeyboardEventListener * listener ) {
    keyboardListener_ = listener;
}

void ApplicationWin32Imp::addMouseListener( MouseEventListener * listener ) {
    mouseListener_ = listener;
}

int ApplicationWin32Imp::getScreenWidth() {
    return width_;
}

int ApplicationWin32Imp::getScreenHeight() {
    return height_;
}

bool ApplicationWin32Imp::isWindowedMode() {
    return bWindowedMode_;
}

wstring ApplicationWin32Imp::getScreenTitle() {
    return title_;
}

ApplicationWin32Imp::ApplicationWin32Imp()
{
    keyboardListener_ = &nullKeyboardListener_;
    mouseListener_ = &nullMouseListener_;
}

void ApplicationWin32Imp::mainLoop() {
    //DXUTMainLoop(); // Enter into the DXUT render loop

    HWND hWnd = DXUTGetHWND();
    HACCEL hAccel = NULL;

    bool bGotMsg;
    MSG msg;
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

    while( WM_QUIT != msg.message )
    {
        // Use PeekMessage() so we can use idle time to render the scene. 
        bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

        if( bGotMsg )
        {
            // Translate and dispatch the message
            if( hWnd == NULL || // hAccel == NULL || 
                0 == TranslateAccelerator( hWnd, hAccel, &msg ) )
            {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            }
        }
        else
        {
            // Render a frame during idle time (no messages are waiting)
            render_->render();
        }
    }
}

//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT ApplicationWin32Imp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
                     void* pUserContext )
{
    /*
    App * const app = (App *) pUserContext;

    // Pass messages to dialog resource manager calls so GUI state is updated correctly
    *pbNoFurtherProcessing = app->eventListener_->dialogResourceManager_.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass messages to settings dialog if its active
    if( app->eventListener_->settingsDlg_.IsActive() )
    {
        app->eventListener_->settingsDlg_.MsgProc( hWnd, uMsg, wParam, lParam );
        return 0;
    }

    // Give the dialogs a chance to handle the message first
    *pbNoFurtherProcessing = app->eventListener_->hud_.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;
    *pbNoFurtherProcessing = app->eventListener_->sampleUI_.MsgProc( hWnd, uMsg, wParam, lParam );
    if( *pbNoFurtherProcessing )
        return 0;

    // Pass all remaining windows messages to camera so it can respond to user input
    app->eventListener_->camera_.HandleMessages( hWnd, uMsg, wParam, lParam );

    */
    return 0;
}


//--------------------------------------------------------------------------------------
// Handle key presses
//--------------------------------------------------------------------------------------
void ApplicationWin32Imp::OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext )
{
}




}
