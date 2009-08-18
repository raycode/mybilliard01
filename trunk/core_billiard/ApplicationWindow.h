#pragma once
namespace my_render {


MY_INTERFACE ApplicationWindow {
    virtual ~ApplicationWindow() {}

    virtual void start() PURE;

    virtual bool setRender( Render * ) PURE;
    virtual Render * getRender() PURE;

    virtual void setScreenX( int x ) PURE;
    virtual void setScreenY( int y ) PURE;
    virtual void setScreenWidth( int width ) PURE;
    virtual void setScreenHeight( int height ) PURE;
    virtual void setWindowedMode( bool ) PURE;
    virtual void setScreenTitle( wstring title ) PURE;

    virtual int getScreenX() PURE;
    virtual int getScreenY() PURE;
    virtual int getScreenWidth() PURE;
    virtual int getScreenHeight() PURE;
    virtual bool isWindowedMode() PURE;
    virtual const wchar_t * getScreenTitle() PURE;

    // listener
    virtual void addKeyboardListener( KeyboardEventListener * listener ) PURE;
    virtual void addMouseListener( MouseEventListener * listener ) PURE;

};


}
