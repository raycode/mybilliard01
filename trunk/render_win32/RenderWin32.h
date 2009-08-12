#pragma once
namespace my_render_win32 {


INTERFACE_ RenderWin32 : EXTENDS_INTERFACE_( Render ) {
public:
    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) = 0;
    virtual void destroyDevice() = 0;

    virtual bool isDeviceCreated() = 0;
    virtual void* getNativeDevice() = 0;

    virtual void force_displayReset() = 0;

    virtual bool isWindowed() = 0;
    virtual void toggleFullScreen() = 0;

    virtual void setHWND( HWND ) = 0;
    virtual HWND getHWND() = 0;

    virtual void setCursorPosition( int x, int y ) = 0;
    virtual void showCursor( bool ) = 0;

    virtual int getFPS() = 0;

};

}