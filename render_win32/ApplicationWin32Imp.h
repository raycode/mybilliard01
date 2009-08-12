#pragma once
namespace my_render_win32_imp {

//==================================================
// This class is dependant on Win32 system.
// It is supposed to work for DirectX and OpenGL.
//==================================================


class ApplicationWin32Imp : IMPLEMENTS_( ApplicationWin32 ) {
public: // from ApplicationWindow
    virtual void start() OVERRIDE; // main loop

    virtual bool setRender( Render * ) OVERRIDE;
    virtual Render * getRender() OVERRIDE;

    virtual void setScreenX( int x ) OVERRIDE;
    virtual void setScreenY( int y ) OVERRIDE;
    virtual void setScreenWidth( int width ) OVERRIDE;
    virtual void setScreenHeight( int height ) OVERRIDE;
    virtual void setWindowedMode( bool ) OVERRIDE;
    virtual void setScreenTitle( wstring title ) OVERRIDE;

    virtual void addKeyboardListener( KeyboardEventListener * listener ) OVERRIDE;
    virtual void addMouseListener( MouseEventListener * listener ) OVERRIDE;

    virtual int getScreenX() OVERRIDE;
    virtual int getScreenY() OVERRIDE;
    virtual int getScreenWidth() OVERRIDE;
    virtual int getScreenHeight() OVERRIDE;
    virtual bool isWindowedMode() OVERRIDE;
    virtual wstring getScreenTitle() OVERRIDE;

public: // from ApplicationWin32
    virtual void addWin32MessageListener( Win32MessageListener * listener ) OVERRIDE;
    virtual HWND getHWND() OVERRIDE;

public:
    ApplicationWin32Imp();
    ~ApplicationWin32Imp();

public: // window manage
    void setMinimized( bool );
    void setMaximized( bool );
    void setSizeInMove( bool );
    bool isMinimized();
    bool isMaximized();
    bool isSizeInMove();

private: // creating window
    bool createWindow();
    bool isWindowCreated();
    void destroyWindow();
    void mainLoop();

    static void handleMessage( MSG & msg );
    static bool MyRegisterClass(HINSTANCE hInstance);
    static HWND InitInstance(HINSTANCE hInstance, int nCmdShow, const wchar_t * szTitle, int x, int y, int width, int height);
    static const wchar_t * getRegisterClassName();

public: // message proc
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
    static ApplicationWin32Imp * g_app_;

private:
    int x_, y_, width_, height_;
    bool bWindowedMode_;
    wstring title_;
    bool bPaused_;

    RenderWin32 * render_;
    KeyboardEventListener * keyboardListener_;
    MouseEventListener * mouseListener_;
    Win32MessageListener * win32MessageListener_;

    NullRenderWin32 nullRenderWin32_;
    NullKeyboardEventListener nullKeyboardListener_;
    NullMouseEventListener nullMouseListener_;
    NullWin32MessageListener nullWin32MessageListener_;

private: //volatile data
    HINSTANCE hInstance_;
    HWND hWnd_;
    HACCEL hAccelTable_;

    bool bMinimized_, bMaximized_, bSizeInMove_;
    Render * actualRender_;

    MY_UNIT_TEST_BACKDOOR;
};


}