#include "StdAfx.h"
#include "my_app.h"

//#define DEBUG_KEY_CODE
#define KEY_UP_ARROW 38
#define KEY_LEFT_ARROW 37
#define KEY_RIGHT_ARROW 39
#define KEY_DOWN_ARROW 40
#define KEY_H 72
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_P 80
#define KEY_A 65
#define KEY_S 83
#define KEY_D 68
#define KEY_W 87
#define KEY_F 70
#define KEY_Z 90
#define KEY_R 82
#define KEY_TAB 9

MyInputListenerImp::MyInputListenerImp( BilliardControl * billiardControl, ApplicationWindow * app )
: billiardControl_( billiardControl )
, app_( app )
, cameraState_( billiardControl->getActiveCamera()->getState() )
{
    mouseState_.setCamera( billiardControl->getActiveCamera() );
    mouseState_.setBilliardControl( billiardControl );
    mouseState_.setPitchSensitivity( 0.05f );
    mouseState_.setRotationSensitivity( 0.005f );
    billiardControl->getActiveCamera()->setMovingSpeed( 20.f );
    cameraState_->mode.changeToAimView();
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
            if( cameraState_->isMoveView() ) cameraState_->move.beginMoveForward();
            break;
        case KEY_LEFT_ARROW:
        case KEY_A:
            if( cameraState_->isMoveView() ) cameraState_->move.beginMoveLeft();
            else if( cameraState_->isAimView() ) cameraState_->aim.beginAimRight();
            else if( cameraState_->isTopView() ) cameraState_->top.beginRotateLeft();
            break;
        case KEY_RIGHT_ARROW:
        case KEY_D:
            if( cameraState_->isMoveView() ) cameraState_->move.beginMoveRight();
            else if( cameraState_->isAimView() ) cameraState_->aim.beginAimLeft();
            else if( cameraState_->isTopView() ) cameraState_->top.beginRotateRight();
            break;
        case KEY_DOWN_ARROW:
        case KEY_S:
            if( cameraState_->isMoveView() ) cameraState_->move.beginMoveBackward();
            break;

        case KEY_H:
            if( cameraState_->isMoveView() ) cameraState_->rotate.beginRotateCounterClockWiseByZ();
            else if( cameraState_->isAimView() ) cameraState_->aim.beginAimRight();
            break;
        case KEY_J: if( cameraState_->isMoveView() ) cameraState_->rotate.beginPitchDown(); break;
        case KEY_K: if( cameraState_->isMoveView() ) cameraState_->rotate.beginPitchUp(); break;
        case KEY_L:
            if( cameraState_->isMoveView() ) cameraState_->rotate.beginRotateClockWiseByZ();
            else if( cameraState_->isAimView() ) cameraState_->aim.beginAimLeft();
            break;

        case KEY_TAB:
            if( cameraState_->isMoveView() ) cameraState_->mode.changeToAimView();
            else if( cameraState_->isAimView() ) cameraState_->mode.changeToTopView();
            else if( cameraState_->isTopView() ) cameraState_->mode.changeToMoveView();
            break;

        case KEY_F:
            app_->setWindowedMode( ! app_->isWindowedMode() );
            break;
        case VK_SPACE:
            if( cameraState_->isAimView() )
                cameraState_->aim.beginShoot();
            break;
        case KEY_R:
            if( GetAsyncKeyState( VK_SHIFT ) != NULL )
                restart();
            else
                bringCueBallBack();
            break;
        case KEY_P:
            togglePause();
            break;
    }
}

void MyInputListenerImp::keyUp( unsigned int key, bool bAlt )
{
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
        case KEY_W:
            if( cameraState_->isMoveView() ) cameraState_->move.endMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
        case KEY_A:
            if( cameraState_->isMoveView() ) cameraState_->move.endMoveLeft();
            else if( cameraState_->isAimView() ) cameraState_->aim.endAimRight();
            else if( cameraState_->isTopView() ) cameraState_->top.endRotateLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
        case KEY_D:
            if( cameraState_->isMoveView() ) cameraState_->move.endMoveRight();
            else if( cameraState_->isAimView() ) cameraState_->aim.endAimLeft();
            else if( cameraState_->isTopView() ) cameraState_->top.endRotateRight();
            break;
        case KEY_DOWN_ARROW: // down arrow
        case KEY_S:
            if( cameraState_->isMoveView() ) cameraState_->move.endMoveBackward();
            break;

        case KEY_H:
            if( cameraState_->isMoveView() ) cameraState_->rotate.endRotateCounterClockWiseByZ();
            else if( cameraState_->isAimView() ) cameraState_->aim.endAimRight();
            break;
        case KEY_J: if( cameraState_->isMoveView() ) cameraState_->rotate.endPitchDown(); break;
        case KEY_K: if( cameraState_->isMoveView() ) cameraState_->rotate.endPitchUp(); break;
        case KEY_L:
            if( cameraState_->isMoveView() ) cameraState_->rotate.endRotateClockWiseByZ();
            else if( cameraState_->isAimView() ) cameraState_->aim.endAimLeft();
            break;

        case VK_SPACE:
            if( cameraState_->isAimView() ) cameraState_->aim.endShoot();
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
        mouseState_.MouseStateSMC::buttonDown( hWnd, iMouseX, iMouseY );
        return TRUE;

    case WM_LBUTTONUP:
        mouseState_.buttonUp();
        return TRUE;

    case WM_CAPTURECHANGED:
        if( ( HWND )lParam != hWnd )
            mouseState_.captureReleased();
        return TRUE;

    case WM_MOUSEMOVE:
        mouseState_.MouseStateSMC::move( iMouseX, iMouseY );
        return TRUE;
    }
    return true;
}

void MyInputListenerImp::bringCueBallBack() {
    billiardControl_->bringCueBallBack();
}

void MyInputListenerImp::togglePause() {
    billiardControl_->pause( ! billiardControl_->isPaused() );
}

void MyInputListenerImp::restart() {
    billiardControl_->restart();
}


