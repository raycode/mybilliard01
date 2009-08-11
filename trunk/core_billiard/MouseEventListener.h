#pragma once
namespace my_render {


INTERFACE_ MouseEventListener {
public:
    virtual void onEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta ) = 0;

public: virtual ~MouseEventListener() {}
};


}
