#pragma once

class App {
public:
    void init();
    int mainLoop();

public:
    App();
    ~App();

private:
    RenderPtr render_;
    RenderErrorListenerPtr errorListener_;
    RenderEventListenerImpPtr eventListener_;

public: // static callback
    static LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext );
    static void CALLBACK OnKeyboard( UINT nChar, bool bKeyDown, bool bAltDown, void* pUserContext );
    static void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );
    static void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext );

};

