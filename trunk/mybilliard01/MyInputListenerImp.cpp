#include "StdAfx.h"
#include "my_app.h"

#define DEBUG_KEY_CODE
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
#define KEY_F 70
#define KEY_Z 90
#define KEY_R 82

MyInputListenerImp::MyInputListenerImp( MyRenderEventListenerImp * renderListener, ApplicationWindow * app )
: renderListener_( renderListener )
, app_( app )
, bDrag_( false )
, bAiming_( false )
, bNeedToStoreDownPt_( false )
, aimableMaxDist_( 60.f )
{
    rotationSensitivity_ = 0.005f;
    pitchSensitivity_ = 0.05f;
    getCamera()->setMovingSpeed( 20.f );
}

void MyInputListenerImp::keyDown( unsigned int key, bool bAlt ) {
#ifdef DEBUG_KEY_CODE
    wchar_t tmp[256];
    _snwprintf_s( tmp, 256, L"key = %d (alt = %s)\n", key, bAlt ? L"true": L"false" );
    OutputDebugStr( tmp );
#endif
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
        case KEY_F:
            app_->setWindowedMode( ! app_->isWindowedMode() );
            break;
        case KEY_Z:
            beginAimBall();
            break;
        case VK_SPACE:
            shot();
            break;
        case KEY_R:
            bringCueBallBack();
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
        case KEY_Z:
            endAimBall();
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
void MyInputListenerImp::stopMoving() {
    endMoveForward();
    endMoveLeft();
    endMoveRight();
    endMoveBackward();
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
void MyInputListenerImp::stopRotate() {
    endRotateClockWiseByZ();
    endRotateCounterClockWiseByZ();
    endPitchDown();
    endPitchUp();
}


bool MyInputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    // Current mouse position
    const int iMouseX = ( short )LOWORD( lParam );
    const int iMouseY = ( short )HIWORD( lParam );

    switch( uMsg )
    {
    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        {
            SetCapture( hWnd );
            OnBeginDrag( iMouseX, iMouseY );
        }
        return TRUE;

    case WM_LBUTTONUP:
        {
            ReleaseCapture();
            OnEndDrag();
        }
        return TRUE;
    case WM_CAPTURECHANGED:
        if( ( HWND )lParam != hWnd )
        {
            ReleaseCapture();
            OnEndDrag();
        }
        return TRUE;

    case WM_MOUSEMOVE:
        if( ( MK_LBUTTON & wParam ) || bAiming_ )
        {
            OnMove( iMouseX, iMouseY );
        }
        return TRUE;
    }
    return true;
}

void MyInputListenerImp::OnBeginDrag( int nX, int nY )
{
    bDrag_ = true;
    m_vDownPt = NxVec3( (float) nX, (float) nY, 0.f );
}

void MyInputListenerImp::OnEndDrag()
{
    bDrag_ = false;
}

void MyInputListenerImp::beginAimBall()
{
    bAiming_ = true;
    bNeedToStoreDownPt_ = true;
    OutputDebugStr( L"begin aim ball.\n" );

    const NxVec3 cueBallPos = renderListener_->getBallPosition();
    getCamera()->lookAtBall( cueBallPos );
    
    getCamera()->setMovementToFixedHeight( 35.f );
}
void MyInputListenerImp::endAimBall()
{
    bAiming_ = false;
    getCamera()->setMovementToFixedHeight( 45.f );
}

void MyInputListenerImp::OnMove( int nX, int nY )
{
    if( bAiming_ )
    {
        m_vCurrentPt = NxVec3( (float) nX, (float) nY, 0.f );
        if( bNeedToStoreDownPt_ ) { m_vDownPt = m_vCurrentPt; bNeedToStoreDownPt_ = false; }

        const NxVec3 diff = m_vCurrentPt - m_vDownPt;
        m_vDownPt = m_vCurrentPt;

        const NxExtendedVec3 currentPosition = getCamera()->getPosition();
        const NxVec3 cueBallPos = renderListener_->getBallPosition();

        if( isCloseEnoughToAim( currentPosition, cueBallPos ) )
        {
            getCamera()->moveClockWiseAroundBall( diff.x * rotationSensitivity_, cueBallPos );
            getCamera()->lookAtBall( cueBallPos );
            return;
        }
    }

    if( bDrag_ )
    {
        m_vCurrentPt = NxVec3( (float) nX, (float) nY, 0.f );
        const NxVec3 diff = m_vCurrentPt - m_vDownPt;
        m_vDownPt = m_vCurrentPt;

        getCamera()->rotateClockWiseByZ( diff.x * rotationSensitivity_ );
        getCamera()->pitchDown( diff.y * pitchSensitivity_ );
    }
}

MyCamera * MyInputListenerImp::getCamera() {
    return renderListener_->getMyCamera();
}

bool MyInputListenerImp::isCloseEnoughToAim( NxExtendedVec3 cameraPos, NxVec3 ballPos ) {
    cameraPos -= ballPos;
    OutputDebugStr( (wstring(L"dist: ") + DebugHelper::getStringFromInt( (int) cameraPos.magnitude() ) + L"\n").c_str() );
    return cameraPos.magnitude() < aimableMaxDist_;
}

void MyInputListenerImp::shot() {
    renderListener_->shotCueBall();
}

void MyInputListenerImp::bringCueBallBack() {
    renderListener_->bringCueBallBack();
}

void MyInputListenerImp::selectBall( int xPos, int yPos )
{

}

