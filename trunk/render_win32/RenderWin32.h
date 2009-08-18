#pragma once
namespace my_render_win32 {


MY_INTERFACE RenderWin32 : EXTENDS_INTERFACE( Render ) {

    virtual void renderOneFrame() PURE;

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) PURE;
    virtual void destroyDevice() PURE;

    virtual bool isDeviceCreated() PURE;

    virtual void force_displayReset() PURE;

    virtual bool isWindowed() PURE;
    virtual void toggleFullScreen() PURE;

    virtual void setHWND( HWND ) PURE;
    virtual HWND getHWND() PURE;

    virtual void setCursorPosition( int x, int y ) PURE;
    virtual void showCursor( bool ) PURE;

    virtual int getFPS() PURE;

};

}