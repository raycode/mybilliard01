#pragma once
namespace my_render_win32_imp {

//==================================================
// This class is dependant on Win32 system.
// It is supposed to work for DirectX and OpenGL.
//==================================================


class ApplicationWin32Imp : IMPLEMENTS_INTERFACE( ApplicationWin32 ) {
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

    virtual int getScreenX() OVERRIDE;
    virtual int getScreenY() OVERRIDE;
    virtual int getScreenWidth() OVERRIDE;
    virtual int getScreenHeight() OVERRIDE;
    virtual bool isWindowedMode() OVERRIDE;
    virtual const wchar_t * getScreenTitle() OVERRIDE;

    virtual void addKeyboardListener( KeyboardEventListener * listener ) OVERRIDE;
    virtual void addMouseListener( MouseEventListener * listener ) OVERRIDE;

public: // from ApplicationWin32
    virtual void addWin32MessageListener( Win32MessageListener * listener ) OVERRIDE;
    virtual HWND getHWND() OVERRIDE;
    virtual const wchar_t * getRegisterClassName() OVERRIDE;

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
    bool isActive();
    void setActive( bool );

private: // creating window
    bool createWindow();
    bool isWindowCreated();
    void destroyWindow();
    void mainLoop();

    static void handleMessage( MSG & msg );
    bool MyRegisterClass(HINSTANCE hInstance);
    HWND InitInstance(HINSTANCE hInstance, int nCmdShow, int x, int y, int width, int height);

private: // message proc
    static ApplicationWin32Imp * g_app_;
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

    static void CALLBACK MsgProcKeyboard(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static void CALLBACK MsgProcMouse(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK MsgProcSystem(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static void CALLBACK MsgProcSystem_WM_SIZE( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_GETMINMAXINFO( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_ENTERSIZEMOVE( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_EXITSIZEMOVE( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_MOUSEMOVE( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static bool CALLBACK MsgProcSystem_WM_SETCURSOR( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_ACTIVATEAPP( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static bool CALLBACK MsgProcSystem_WM_POWERBROADCAST( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static int CALLBACK MsgProcSystem_WM_SYSKEYDOWN( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_KEYDOWN( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static void CALLBACK MsgProcSystem_WM_CLOSE( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static int CALLBACK MsgProcSystem_WM_SYSCOMMAND( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

private:
    int x_, y_, width_, height_;
    bool bWindowedMode_;
    wstring title_;
    bool bPaused_;

    RenderWin32 * render_;
    KeyboardEventListener * keyboardListener_;
    MouseEventListener * mouseListener_;
    Win32MessageListener * win32MessageListener_;

    RenderWin32Null nullRenderWin32_;
    KeyboardEventListenerNull nullKeyboardListener_;
    MouseEventListenerNull nullMouseListener_;
    Win32MessageListenerNull nullWin32MessageListener_;

private: //volatile data
    HINSTANCE hInstance_;
    HWND hWnd_;
    HACCEL hAccelTable_;

    bool bMinimized_, bMaximized_, bSizeInMove_, bActive_;
    RenderWin32 * actualRender_;

    MY_UNIT_TEST_BACKDOOR;
};


}