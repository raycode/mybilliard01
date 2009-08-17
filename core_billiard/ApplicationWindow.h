#pragma once
namespace my_render {


MY_INTERFACE ApplicationWindow {
    virtual ~ApplicationWindow() {}

    virtual void start() = 0;

    virtual bool setRender( Render * ) = 0;
    virtual Render * getRender() = 0;

    virtual void setScreenX( int x ) = 0;
    virtual void setScreenY( int y ) = 0;
    virtual void setScreenWidth( int width ) = 0;
    virtual void setScreenHeight( int height ) = 0;
    virtual void setWindowedMode( bool ) = 0;
    virtual void setScreenTitle( wstring title ) = 0;

    virtual int getScreenX() = 0;
    virtual int getScreenY() = 0;
    virtual int getScreenWidth() = 0;
    virtual int getScreenHeight() = 0;
    virtual bool isWindowedMode() = 0;
    virtual const wchar_t * getScreenTitle() = 0;

    // listener
    virtual void addKeyboardListener( KeyboardEventListener * listener ) = 0;
    virtual void addMouseListener( MouseEventListener * listener ) = 0;

};


}
