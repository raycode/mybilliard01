#include "DXUT.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {

ApplicationWin32Imp * ApplicationWin32Imp::g_app_ = NULL;

ApplicationWin32Imp::ApplicationWin32Imp()
: x_( 10 ), y_( 10 )
, width_( 640 ), height_( 480 )
, bWindowedMode_( true )
, bPaused_( false )
, render_( NULL )
, hWnd_( NULL )
, bMinimized_( false )
, bMaximized_( false )
, bSizeInMove_( false )
{
    keyboardListener_ = &nullKeyboardListener_;
    mouseListener_ = &nullMouseListener_;

    if( NULL != g_app_ )
        throw exception();
    g_app_ = this;
}

void ApplicationWin32Imp::openWindow() {
    if( NULL == render_ )
        throw exception();

    if( false == createWindow() )
        throw exception();

    if( false == render_->createDevice( isWindowedMode(), getScreenWidth(), getScreenHeight() ) ) {
        destroyWindow();
        throw exception();
    }

    mainLoop();

    render_->releaseDevice();

    destroyWindow();
}

bool ApplicationWin32Imp::isWindowOpen() {
    return NULL != hWnd_;
}

const wchar_t * ApplicationWin32Imp::getRegisterClassName() {
    return L"ApplicationWin32ImpClass";
}

bool ApplicationWin32Imp::createWindow()
{
    if( isWindowOpen() )
        return false;

    HICON hIcon = NULL;
    HMENU hMenu = NULL;

    {
        hInstance_ = ( HINSTANCE )GetModuleHandle( NULL );

        WCHAR szExePath[MAX_PATH];
        GetModuleFileName( NULL, szExePath, MAX_PATH );
        if( hIcon == NULL ) // If the icon is NULL, then use the first one found in the exe
            hIcon = ExtractIcon( hInstance_, szExePath, 0 );

        // Register the windows class
        WNDCLASS wndClass;
        wndClass.style = CS_DBLCLKS;
        wndClass.lpfnWndProc = ApplicationWin32Imp::MsgProc;
        wndClass.cbClsExtra = 0;
        wndClass.cbWndExtra = 0;
        wndClass.hInstance = hInstance_;
        wndClass.hIcon = hIcon;
        wndClass.hCursor = LoadCursor( NULL, IDC_ARROW );
        wndClass.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
        wndClass.lpszMenuName = NULL;
        wndClass.lpszClassName = getRegisterClassName();

        if( !RegisterClass( &wndClass ) )
        {
            DWORD dwError = GetLastError();
            if( dwError != ERROR_CLASS_ALREADY_EXISTS )
                return false;
        }
    }

    {
        int nDefaultWidth = getScreenHeight();
        int nDefaultHeight = getScreenHeight();

        RECT rc;
        SetRect( &rc, 0, 0, nDefaultWidth, nDefaultHeight );
        AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, ( hMenu != NULL ) ? true : false );

        // Create the render window
        hWnd_ = CreateWindow( getRegisterClassName(), getScreenTitle().c_str(), WS_OVERLAPPEDWINDOW,
            getScreenX(), getScreenY(),
            ( rc.right - rc.left ), ( rc.bottom - rc.top ), 0,
            hMenu, hInstance_, 0 );
        if( NULL == hWnd_ )
            return false;

        //GetDXUTState().SetHWNDDeviceFullScreen( hWnd );
        //GetDXUTState().SetHWNDDeviceWindowed( hWnd );
    }

    return true;
}

void ApplicationWin32Imp::destroyWindow() {
    DestroyWindow( hWnd_ );
    hWnd_ = NULL;
}


void ApplicationWin32Imp::setRender( Render * render ) {
    render_ = render;
}

int ApplicationWin32Imp::getScreenX() {
    return x_;
}

int ApplicationWin32Imp::getScreenY() {
    return y_;
}

void ApplicationWin32Imp::setScreenX( int x ) {
    x_ = x;
}

void ApplicationWin32Imp::setScreenY( int y ) {
    y_ = y;
}

void ApplicationWin32Imp::setMinimized( bool val ) {
    bMinimized_ = val;
}

void ApplicationWin32Imp::setMaximized( bool val ) {
    bMaximized_ = val;
}

bool ApplicationWin32Imp::isMinimized() {
    return bMinimized_;
}

bool ApplicationWin32Imp::isMaximized() {
    return bMaximized_;
}

bool ApplicationWin32Imp::isSizeInMove() {
    return bSizeInMove_;
}

void ApplicationWin32Imp::setSizeInMove( bool val ) {
    bSizeInMove_ = val;
}

void ApplicationWin32Imp::setScreenWidth( int width ) {
    width_ = width;
}

void ApplicationWin32Imp::setScreenHeight( int height ) {
    height_ = height;
}

void ApplicationWin32Imp::setWindowedMode( bool mode ) {
    bWindowedMode_ = mode;

    if( isWindowOpen() && (isWindowedMode() != mode ) && render_->isDeviceCreated() )
        render_->toggleFullScreen();
}

bool ApplicationWin32Imp::isWindowedMode() {
    if( isWindowOpen() && render_->isDeviceCreated() )
        return render_->isWindowed();
    return bWindowedMode_;
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

wstring ApplicationWin32Imp::getScreenTitle() {
    return title_;
}

void ApplicationWin32Imp::mainLoop() {
    //DXUTMainLoop(); // Enter into the DXUT render loop
    HACCEL hAccel = NULL;

    MSG msg;
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

    while( WM_QUIT != msg.message )
    {
        // Use PeekMessage() so we can use idle time to render the scene. 
        const bool bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

        if( bGotMsg )
        {
            // Translate and dispatch the message
            if( hWnd_ == NULL || hAccel == NULL || 
                0 == TranslateAccelerator( hWnd_, hAccel, &msg ) )
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
//LRESULT CALLBACK ApplicationWin32Imp::MsgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
//{
//    App * const app = (App *) pUserContext;
//
//    // Pass messages to dialog resource manager calls so GUI state is updated correctly
//    *pbNoFurtherProcessing = app->eventListener_->dialogResourceManager_.MsgProc( hWnd, uMsg, wParam, lParam );
//    if( *pbNoFurtherProcessing )
//        return 0;
//
//    // Pass messages to settings dialog if its active
//    if( app->eventListener_->settingsDlg_.IsActive() )
//    {
//        app->eventListener_->settingsDlg_.MsgProc( hWnd, uMsg, wParam, lParam );
//        return 0;
//    }
//
//    // Give the dialogs a chance to handle the message first
//    *pbNoFurtherProcessing = app->eventListener_->hud_.MsgProc( hWnd, uMsg, wParam, lParam );
//    if( *pbNoFurtherProcessing )
//        return 0;
//    *pbNoFurtherProcessing = app->eventListener_->sampleUI_.MsgProc( hWnd, uMsg, wParam, lParam );
//    if( *pbNoFurtherProcessing )
//        return 0;
//
//    // Pass all remaining windows messages to camera so it can respond to user input
//    app->eventListener_->camera_.HandleMessages( hWnd, uMsg, wParam, lParam );
//
////    return DefWindowProc(hWnd, Msg, wParam, lParam);
//}
//





}
