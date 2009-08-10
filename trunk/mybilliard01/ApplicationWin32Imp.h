#pragma once
namespace my_render_d3d9_imp {


class ApplicationWin32Imp : IMPLEMENTS_( ApplicationWindow ) {
public: // from ApplicationWindow
    virtual void openWindow(); // main loop

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
    void releaseWindow();
    void mainLoop();

public: // get
    int getScreenWidth();
    int getScreenHeight();
    bool isWindowedMode();
    wstring getScreenTitle();

public: // static
    static LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);
    //static LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
    static void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
    static void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );

private:
    int width_, height_;
    bool bWindowedMode_;
    wstring title_;

    bool bWindowCreated_;
    HINSTANCE hInstance_;
    HWND hWnd_;

    Render * render_;
    KeyboardEventListener * keyboardListener_;
    MouseEventListener * mouseListener_;

    NullKeyboardEventListener nullKeyboardListener_;
    NullMouseEventListener nullMouseListener_;
};


}