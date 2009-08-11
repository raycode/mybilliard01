#pragma once
namespace my_render_d3d9_imp {

//==================================================
// This class is dependant on Win32 system.
// It is supposed to work for DirectX and OpenGL.
//==================================================


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

    virtual void addWin32MessageListener( Win32MessageListener * listener );

private:
    bool createWindow();
    void destroyWindow();
    void mainLoop();

public: // get
    int getScreenX();
    int getScreenY();
    int getScreenWidth();
    int getScreenHeight();
    bool isWindowedMode();
    wstring getScreenTitle();

public: // message proc
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

public: // window manage
    void setMinimized( bool );
    void setMaximized( bool );
    void setSizeInMove( bool );
    bool isMinimized();
    bool isMaximized();
    bool isSizeInMove();

public: // static
    static const wchar_t * getRegisterClassName();
    static ApplicationWin32Imp * g_app_;

private:
    int x_, y_, width_, height_;
    bool bWindowedMode_;
    wstring title_;
    bool bPaused_;

    Render * render_;
    KeyboardEventListener * keyboardListener_;
    MouseEventListener * mouseListener_;
    Win32MessageListener * win32MessageListener_;

    NullKeyboardEventListener nullKeyboardListener_;
    NullMouseEventListener nullMouseListener_;
    NullWin32MessageListener nullWin32MessageListener_;

private: //volatile data
    HINSTANCE hInstance_;
    HWND hWnd_;

    bool bMinimized_, bMaximized_, bSizeInMove_;

};


}