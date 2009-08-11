#pragma once
namespace my_render_win32_imp {

//==================================================
// This class is dependant on Win32 system.
// It is supposed to work for DirectX and OpenGL.
//==================================================


class ApplicationWin32Imp : IMPLEMENTS_( ApplicationWin32 ) {
public: // from ApplicationWindow
    virtual void start(); // main loop
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

public: // from ApplicationWin32
    virtual void addWin32MessageListener( Win32MessageListener * listener );
    virtual HWND getHWND();

public:
    ApplicationWin32Imp();

public: // get
    int getScreenX();
    int getScreenY();
    int getScreenWidth();
    int getScreenHeight();
    bool isWindowedMode();
    wstring getScreenTitle();

public: // window manage
    void setMinimized( bool );
    void setMaximized( bool );
    void setSizeInMove( bool );
    bool isMinimized();
    bool isMaximized();
    bool isSizeInMove();

private: // creating window
    bool createWindow();
    void destroyWindow();
    void mainLoop();

    static void handleMessage( MSG & msg );
    static ATOM MyRegisterClass(HINSTANCE hInstance);
    static bool InitInstance(HINSTANCE hInstance, int nCmdShow, const wchar_t * szTitle, int x, int y, int width, int height);
    static const wchar_t * getRegisterClassName();

public: // message proc
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
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

    NullRender nullRender_;
    NullKeyboardEventListener nullKeyboardListener_;
    NullMouseEventListener nullMouseListener_;
    NullWin32MessageListener nullWin32MessageListener_;

private: //volatile data
    HINSTANCE hInstance_;
    HWND hWnd_;
    HACCEL hAccelTable_;

    bool bMinimized_, bMaximized_, bSizeInMove_;
    Render * actualRender_;

};


}