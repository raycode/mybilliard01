#include "StdAfx.h"
#include "my_app.h"


MyInputListenerImp::MyInputListenerImp( MyRenderEventListenerImp * renderListener ) {
    renderListener_ = renderListener;
}

void MyInputListenerImp::keyDown( unsigned int key, bool bAlt ) {

}

void MyInputListenerImp::keyUp( unsigned int key, bool bAlt ) {

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

bool MyInputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    //if( false == MsgProcDXUT( hWnd, uMsg, wParam, lParam ) )
    //    return false;

    // add more here

    return true;
}

