#pragma once
namespace my_render {


MY_INTERFACE MouseEventListener {
    virtual ~MouseEventListener() {}

    virtual void onMouseEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta ) PURE;

};


}
