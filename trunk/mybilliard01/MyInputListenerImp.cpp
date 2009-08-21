#include "StdAfx.h"
#include "my_app.h"

#define KEY_UP_ARROW 38
#define KEY_LEFT_ARROW 37
#define KEY_RIGHT_ARROW 39
#define KEY_DOWN_ARROW 40

MyInputListenerImp::MyInputListenerImp( MyRenderEventListenerImp * renderListener ) {
    renderListener_ = renderListener;
}

void MyInputListenerImp::keyDown( unsigned int key, bool bAlt ) {
    //wchar_t tmp[256];
    //_snwprintf_s( tmp, 256, L"key = %d\n", key );
    //OutputDebugStr( tmp );
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
            beginMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
            beginMoveLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
            beginMoveRight();
        case KEY_DOWN_ARROW: // down arrow
            beginMoveBackward();
            break;
    }
}

void MyInputListenerImp::keyUp( unsigned int key, bool bAlt )
{
    switch( key ) {
        case KEY_UP_ARROW: // up arrow
            endMoveForward();
            break;
        case KEY_LEFT_ARROW: // left arrow
            endMoveLeft();
            break;
        case KEY_RIGHT_ARROW: // right arrow
            endMoveRight();
        case KEY_DOWN_ARROW: // down arrow
            endMoveBackward();
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
    if( bRightButton ) rotateCamera( xPos, yPos );
    if( bLeftButton ) selectBall( xPos, yPos );
}

bool MyInputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    return true;
}

MyCamera * MyInputListenerImp::getCamera()
{
    return renderListener_->getMyCamera();
}

void MyInputListenerImp::rotateCamera( int xPos, int yPos )
{

}

void MyInputListenerImp::selectBall( int xPos, int yPos )
{

}

void MyInputListenerImp::beginMoveForward()
{
    //getCamera()->move(  )
}
void MyInputListenerImp::beginMoveLeft()
{

}
void MyInputListenerImp::beginMoveRight()
{

}
void MyInputListenerImp::beginMoveBackward()
{

}
void MyInputListenerImp::endMoveForward()
{

}
void MyInputListenerImp::endMoveLeft()
{

}
void MyInputListenerImp::endMoveRight()
{

}
void MyInputListenerImp::endMoveBackward()
{

}


