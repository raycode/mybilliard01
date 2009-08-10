#include "DXUT.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {


void ApplicationWin32Imp::openWindow() {
    if( false == createWindow() )
        throw exception();

    if( NULL == render_ )
        throw exception();

    if( false == render_->createDevice( isWindowedMode(), getScreenWidth(), getScreenHeight() ) )
         throw exception();

    mainLoop();

    render_->releaseDevice();
}

bool ApplicationWin32Imp::createWindow()
{
    if( bWindowCreated_ )
        return false;

    HICON hIcon = NULL;
    HMENU hMenu = NULL;
    int x = 10;
    int y = 10;
    const wstring registerClassName = getScreenTitle();

    {
        hInstance_ = ( HINSTANCE )GetModuleHandle( NULL );

        WCHAR szExePath[MAX_PATH];
        GetModuleFileName( NULL, szExePath, MAX_PATH );
        if( hIcon == NULL ) // If the icon is NULL, then use the first one found in the exe
            hIcon = ExtractIcon( hInstance_, szExePath, 0 );

        // Register the windows class
        WNDCLASS wndClass;
        wndClass.style = CS_DBLCLKS;
        wndClass.lpfnWndProc = DXUTStaticWndProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = hInstance_;
        wndClass.hIcon = hIcon;
        wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
        wndClass.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
        wndClass.lpszMenuName = NULL;
        wndClass.lpszClassName = registerClassName.c_str();

        if( !RegisterClass( &wndClass ) )
        {
            DWORD dwError = GetLastError();
            if( dwError != ERROR_CLASS_ALREADY_EXISTS )
                return false;
        }

        int nDefaultWidth = 640;
        int nDefaultHeight = 480;

        RECT rc;
        SetRect( &rc, 0, 0, nDefaultWidth, nDefaultHeight );
        AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, ( hMenu != NULL ) ? true : false );

        // Create the render window
        HWND hWnd = CreateWindow( registerClassName.c_str(), getScreenTitle().c_str(), WS_OVERLAPPEDWINDOW,
            x, y, ( rc.right - rc.left ), ( rc.bottom - rc.top ), 0,
            hMenu, hInstance_, 0 );
        if( hWnd == NULL )
            return false;

        //GetDXUTState().SetHWNDDeviceFullScreen( hWnd );
        //GetDXUTState().SetHWNDDeviceWindowed( hWnd );
    }

    bWindowCreated_ = true;
    return true;
}

void ApplicationWin32Imp::releaseWindow() {
    bWindowCreated_ = false;
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
: bWindowCreated_( false )
, render_( NULL )
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
LRESULT ApplicationWin32Imp::MsgProc(HWND, UINT, WPARAM, LPARAM)
//LRESULT ApplicationWin32Imp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing,
//                     void* pUserContext )
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
