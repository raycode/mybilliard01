#include "StdAfx.h"
#include "my_app.h"

#define KEY_UP_ARROW 38
#define KEY_LEFT_ARROW 37
#define KEY_RIGHT_ARROW 39
#define KEY_DOWN_ARROW 40
#define KEY_H 72
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68
#define KEY_W 87

MyInputListenerImp::MyInputListenerImp( MyRenderEventListenerImp * renderListener )
: m_bDrag( false )
{
    renderListener_ = renderListener;
    rotationSensitivity_ = 0.0005f;
    pitchSensitivity_ = 0.01f;
}

void MyInputListenerImp::keyDown( unsigned int key, bool bAlt ) {
    wchar_t tmp[256];
    _snwprintf_s( tmp, 256, L"key = %d\n", key );
    OutputDebugStr( tmp );
    switch( key ) {
        case KEY_UP_ARROW:
        case KEY_W:
            beginMoveForward();
            break;
        case KEY_LEFT_ARROW:
        case KEY_A:
            beginMoveLeft();
            break;
        case KEY_RIGHT_ARROW:
        case KEY_D:
            beginMoveRight();
            break;
        case KEY_DOWN_ARROW:
        case KEY_S:
            beginMoveBackward();
            break;
        case KEY_H:
            beginRotateCounterClockWiseByZ();
            break;
        case KEY_J:
            beginPitchDown();
            break;
        case KEY_K:
            beginPitchUp();
            break;
        case KEY_L:
            beginRotateClockWiseByZ();
            break;
    }
}

void MyInputListenerImp::keyUp( unsigned int key, bool bAlt )
{
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
        case KEY_W:
            endMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
        case KEY_A:
            endMoveLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
        case KEY_D:
            endPitchDown();
            endMoveRight();
        case KEY_DOWN_ARROW: // down arrow
        case KEY_S:
            endMoveBackward();
            break;
        case KEY_H:
            endRotateCounterClockWiseByZ();
            break;
        case KEY_J: // down
            endPitchDown();
            break;
        case KEY_K: // up
            endPitchUp();
            break;
        case KEY_L:
            endRotateClockWiseByZ();
            break;
    }
}

void MyInputListenerImp::onMouseEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta ) 
{
    if( bLeftButton ) selectBall( xPos, yPos );
}

void MyInputListenerImp::beginMoveForward() {
    getCamera()->beginMoveForward();
}
void MyInputListenerImp::beginMoveLeft() {
    getCamera()->beginMoveLeft();
}
void MyInputListenerImp::beginMoveRight() {
    getCamera()->beginMoveRight();
}
void MyInputListenerImp::beginMoveBackward() {
    getCamera()->beginMoveBackward();
}
void MyInputListenerImp::endMoveForward() {
    getCamera()->endMoveForward();
}
void MyInputListenerImp::endMoveLeft() {
    getCamera()->endMoveLeft();
}
void MyInputListenerImp::endMoveRight() {
    getCamera()->endMoveRight();
}
void MyInputListenerImp::endMoveBackward() {
    getCamera()->endMoveBackward();
}

void MyInputListenerImp::beginRotateCounterClockWiseByZ() {
    getCamera()->beginRotateCounterClockWiseByZ();
}
void MyInputListenerImp::beginRotateClockWiseByZ() {
    getCamera()->beginRotateClockWiseByZ();
}
void MyInputListenerImp::endRotateCounterClockWiseByZ() {
    getCamera()->endRotateCounterClockWiseByZ();
}
void MyInputListenerImp::endRotateClockWiseByZ() {
    getCamera()->endRotateClockWiseByZ();
}

void MyInputListenerImp::beginPitchDown() {
    getCamera()->beginPitchDown();
}
void MyInputListenerImp::beginPitchUp() {
    getCamera()->beginPitchUp();
}
void MyInputListenerImp::endPitchDown() {
    getCamera()->endPitchDown();
}
void MyInputListenerImp::endPitchUp() {
    getCamera()->endPitchUp();
}


bool MyInputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    // Current mouse position
    int iMouseX = ( short )LOWORD( lParam );
    int iMouseY = ( short )HIWORD( lParam );

    switch( uMsg )
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        SetCapture( hWnd );
        OnBegin( iMouseX, iMouseY );
        return TRUE;

    case WM_LBUTTONUP:
        ReleaseCapture();
        OnEnd();
        return TRUE;
    case WM_CAPTURECHANGED:
        if( ( HWND )lParam != hWnd )
        {
            ReleaseCapture();
            OnEnd();
        }
        return TRUE;

    case WM_MOUSEMOVE:
        if( MK_LBUTTON & wParam )
        {
            OnMove( iMouseX, iMouseY );
        }
        return TRUE;
    }
    return true;
}

void MyInputListenerImp::OnBegin( int nX, int nY )
{
    m_bDrag = true;
    m_vDownPt = NxVec3( (float) nX, (float) nY, 0.f );
}

void MyInputListenerImp::OnMove( int nX, int nY )
{
    if( m_bDrag )
    {
        m_vCurrentPt = NxVec3( (float) nX, (float) nY, 0.f );
        const NxVec3 diff = m_vCurrentPt - m_vDownPt;
        m_vDownPt = m_vCurrentPt;

        getCamera()->rotateClockWiseByZ( diff.x * rotationSensitivity_ );
        getCamera()->pitchDown( diff.y * pitchSensitivity_ );
    }
}

void MyInputListenerImp::OnEnd()
{
    m_bDrag = false;
}

MyCamera * MyInputListenerImp::getCamera()
{
    return renderListener_->getMyCamera();
}

void MyInputListenerImp::selectBall( int xPos, int yPos )
{

}

