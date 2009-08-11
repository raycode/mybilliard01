#include "my_render_win32_imp.h"
namespace my_render_win32_imp {


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
    setRender( &nullRenderWin32_ );
    addKeyboardListener( &nullKeyboardListener_ );
    addMouseListener( &nullMouseListener_ );
    addWin32MessageListener( &nullWin32MessageListener_ );

    if( NULL != g_app_ )
        throw exception();
    g_app_ = this;
}

ApplicationWin32Imp::~ApplicationWin32Imp() {
    if( isWindowCreated() )
        destroyWindow();
    g_app_ = NULL;
}

void ApplicationWin32Imp::start() {
    if( false == createWindow() )
        throw exception();

    render_->setHWND( getHWND() );

    if( false == render_->createDevice( isWindowedMode(), getScreenWidth(), getScreenHeight() ) ) {
        destroyWindow();
        throw exception();
    }

    mainLoop();

    render_->releaseDevice();

    destroyWindow();
}

HWND ApplicationWin32Imp::getHWND() {
    return hWnd_;
}

const wchar_t * ApplicationWin32Imp::getRegisterClassName() {
    return L"ApplicationWin32ImpClass";
}

bool ApplicationWin32Imp::isWindowCreated() {
    return NULL != hWnd_;
}

bool ApplicationWin32Imp::createWindow()
{
    if( isWindowCreated() ) return false;

    hInstance_ = ( HINSTANCE )GetModuleHandle( NULL );

    if( false == MyRegisterClass( hInstance_ ) )
        return false;

    const int x = getScreenX();
    const int y = getScreenY();
    const int width = getScreenWidth();
    const int height = getScreenHeight();
    const wchar_t * title = getScreenTitle().c_str();
    hWnd_ = InitInstance( hInstance_, SW_SHOW, title, x, y, width, height );

    return NULL != hWnd_;
}


void ApplicationWin32Imp::destroyWindow() {
    DestroyWindow( hWnd_ );
    hWnd_ = NULL;

    UnregisterClass( getRegisterClassName(), hInstance_ );
}


bool ApplicationWin32Imp::setRender( Render * render ) {
    render_ = dynamic_cast< RenderWin32 *>( render );
    const bool bRst = (NULL != render_);
    if( false == bRst )
        render_ = &nullRenderWin32_;

    actualRender_ = render_;
    return bRst;
}

Render * ApplicationWin32Imp::getRender() {
    return render_;
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

    actualRender_ = (val ? &nullRenderWin32_ : (Render*) render_ );
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

    actualRender_ = (val ? (Render*)(&nullRenderWin32_) : render_ );
}

void ApplicationWin32Imp::setScreenWidth( int width ) {
    width_ = width;
}

void ApplicationWin32Imp::setScreenHeight( int height ) {
    height_ = height;
}

void ApplicationWin32Imp::setWindowedMode( bool mode ) {
    bWindowedMode_ = mode;

    if( render_->isDeviceCreated() && render_->isWindowed() != mode )
        render_->toggleFullScreen();
}

bool ApplicationWin32Imp::isWindowedMode() {
    if( render_->isDeviceCreated() )
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

void ApplicationWin32Imp::addWin32MessageListener( Win32MessageListener * listener ) {
    win32MessageListener_ = listener;
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



}
