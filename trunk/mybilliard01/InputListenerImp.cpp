#include "DXUT.h"
#include "my_app.h"


InputListenerImp::InputListenerImp( RenderEventListenerImp * renderListener ) {
    renderListener_ = renderListener;
}

void InputListenerImp::keyDown( unsigned int key, bool bAlt ) {

}

void InputListenerImp::keyUp( unsigned int key, bool bAlt ) {

}

void InputListenerImp::onEvent(
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

