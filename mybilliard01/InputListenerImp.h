#pragma once


class InputListenerImp
    : IMPLEMENTS_( KeyboardEventListener )
    , IMPLEMENTS_( MouseEventListener )
{
public: // from KeyboardEventListener
    virtual void keyDown( unsigned int key, bool bAlt );
    virtual void keyUp( unsigned int key, bool bAlt );

public: // from MouseEventListener
    virtual void onEvent(
        int xPos,
        int yPos,
        bool bLeftButton,
        bool bRightButton, 
        bool bMiddleButton, 
        bool bSideButton1, 
        bool bSideButton2, 
        int nMouseWheelDelta );

public:
    InputListenerImp( RenderEventListenerImp * renderListener );

private:
    RenderEventListenerImp * renderListener_;
};


