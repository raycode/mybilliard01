#pragma once
namespace my_render_d3d9_imp {


class MouseEventListenerImp : IMPLEMENTS_( MouseEventListener ) {
public:
    virtual void onEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta );

};


}
