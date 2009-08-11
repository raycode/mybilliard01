#pragma once
namespace my_render {


class NullMouseEventListener : IMPLEMENTS_( MouseEventListener ) {
public:
    virtual void onMouseEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta ) {}
};


}
