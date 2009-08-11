#pragma once
namespace my_render_d3d9_imp {


class ApplicationWin32Imp : IMPLEMENTS_( ApplicationWindow ) {
public: // from ApplicationWindow
    virtual void openWindow(); // main loop
    virtual bool isWindowOpen();

    virtual void setScreenX( int x );
    virtual void setScreenY( int y );
    virtual void setScreenWidth( int width );
    virtual void setScreenHeight( int height );
    virtual void setWindowedMode( bool );
    virtual void setScreenTitle( wstring title );

    virtual void setRender( Render * );
    virtual void addKeyboardListener( KeyboardEventListener * listener );
    virtual void addMouseListener( MouseEventListener * listener );

public:
    ApplicationWin32Imp();

    bool createWindow();
    void destroyWindow();
    void mainLoop();

    static const wchar_t * getRegisterClassName();

public: // get
    int getScreenX();
    int getScreenY();
    int getScreenWidth();
    int getScreenHeight();
    bool isWindowedMode();
    wstring getScreenTitle();

public: // message proc
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
    static ApplicationWin32Imp * g_app_;

public: // window manage
    void setMinimized( bool );
    void setMaximized( bool );
    void setSizeInMove( bool );
    bool isMinimized();
    bool isMaximized();
    bool isSizeInMove();

private:
    int x_, y_, width_, height_;
    bool bWindowedMode_;
    wstring title_;
    bool bPaused_;

    Render * render_;
    KeyboardEventListener * keyboardListener_;
    MouseEventListener * mouseListener_;

    NullKeyboardEventListener nullKeyboardListener_;
    NullMouseEventListener nullMouseListener_;

private: //volatile data
    HINSTANCE hInstance_;
    HWND hWnd_;

    bool bMinimized_, bMaximized_, bSizeInMove_;

};


}