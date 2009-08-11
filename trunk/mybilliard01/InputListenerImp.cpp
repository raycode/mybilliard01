#include "StdAfx.h"
#include "my_app.h"


InputListenerImp::InputListenerImp( RenderEventListenerImp * renderListener ) {
    renderListener_ = renderListener;
}

void InputListenerImp::keyDown( unsigned int key, bool bAlt ) {

}

void InputListenerImp::keyUp( unsigned int key, bool bAlt ) {

}

void InputListenerImp::onMouseEvent(
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

bool InputListenerImp::MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    if( false == MsgProcDXUT( hWnd, uMsg, wParam, lParam ) )
        return false;

    // add more here

    return true;
}

