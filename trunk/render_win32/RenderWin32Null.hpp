#pragma once
namespace my_render_win32 {


NULL_OBJECT( RenderWin32 ), public RenderNull {

    virtual void renderOneFrame() OVERRIDE {}

    virtual bool createDevice( bool bWindowed, int nSuggestedWidth, int nSuggestedHeight ) OVERRIDE { return false; }
    virtual void destroyDevice() OVERRIDE {}

    virtual bool isDeviceCreated() OVERRIDE { return false; }

    virtual void force_displayReset() OVERRIDE {}

    virtual bool isWindowed() OVERRIDE { return true; }
    virtual void toggleFullScreen() OVERRIDE {}

    virtual void setHWND( HWND ) OVERRIDE {}
    virtual HWND getHWND() OVERRIDE { return NULL; }

    virtual void setCursorPosition( int x, int y ) OVERRIDE {}
    virtual void showCursor( bool ) OVERRIDE {}

    virtual int getFPS() OVERRIDE { return 0; }

};


}
