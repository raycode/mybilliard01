#pragma once
namespace my_render {


INTERFACE_ ApplicationWindow {
public:
    virtual void openWindow() = 0;
    virtual void setRender( Render * ) = 0;

    virtual void setScreenWidth( int width ) = 0;
    virtual void setScreenHeight( int height ) = 0;
    virtual void setWindowedMode( bool ) = 0;
    virtual void setScreenTitle( wstring title ) = 0;

public: // listener
    virtual void addKeyboardListener( KeyboardEventListener * listener ) = 0;
    virtual void addMouseListener( MouseEventListener * listener ) = 0;

public: virtual ~ApplicationWindow() {}
};


}
