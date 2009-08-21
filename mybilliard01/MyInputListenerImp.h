#pragma once


class MyInputListenerImp
    : IMPLEMENTS_INTERFACE( KeyboardEventListener )
    , IMPLEMENTS_INTERFACE( MouseEventListener )
    , IMPLEMENTS_INTERFACE( Win32MessageListener )
{
public: // from KeyboardEventListener
    virtual void keyDown( unsigned int key, bool bAlt );
    virtual void keyUp( unsigned int key, bool bAlt );

public: // from MouseEventListener
    virtual void onMouseEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta );

public: // from Win32MessageListener
    virtual bool MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

public:
    MyInputListenerImp( MyRenderEventListenerImp * renderListener );

private:
    MyCamera * getCamera();

private: // move
    void beginMoveForward();
    void beginMoveLeft();
    void beginMoveRight();
    void beginMoveBackward();
    void endMoveForward();
    void endMoveLeft();
    void endMoveRight();
    void endMoveBackward();

    void selectBall( int xPos, int yPos );
    void rotateCamera( int xPos, int yPos );

private:
    MyRenderEventListenerImp * renderListener_;
};


