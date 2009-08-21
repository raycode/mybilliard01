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

private: // rotate
    void beginRotateClockWiseByZ();
    void beginRotateCounterClockWiseByZ();
    void endRotateClockWiseByZ();
    void endRotateCounterClockWiseByZ();

    void beginPitchDown();
    void beginPitchUp();
    void endPitchDown();
    void endPitchUp();

    void selectBall( int xPos, int yPos );
    void rotateCamera( int xPos, int yPos );

private: // mouse
    void OnBegin( int nX, int nY );
    void OnMove( int nX, int nY );
    void OnEnd();
    D3DXVECTOR3 ScreenToVector( float fScreenPtX, float fScreenPtY );
    //D3DXQUATERNION QuatFromBallPoints( const D3DXVECTOR3& vFrom, const D3DXVECTOR3& vTo );
    void SetOffset( INT nX, INT nY ) { m_Offset.x = nX; m_Offset.y = nY; }
    POINT m_Offset;   // window offset, or upper-left corner of window

private:
    MyRenderEventListenerImp * renderListener_;

private: // mouse
    bool m_bDrag;
    D3DXQUATERNION m_qDown;             // Quaternion before button down
    D3DXQUATERNION m_qNow;              // Composite quaternion for current drag
    D3DXVECTOR3 m_vDownPt;           // starting point of rotation arc
    D3DXVECTOR3 m_vCurrentPt;        // current point of rotation arc
    INT m_nWidth;   // arc ball's window width
    INT m_nHeight;  // arc ball's window height
    FLOAT m_fRadius;  // arc ball's radius in screen coords
};


