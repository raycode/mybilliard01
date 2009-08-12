#pragma once
namespace my_render {


class NullKeyboardEventListener : IMPLEMENTS_( KeyboardEventListener ) {
public:
    virtual void keyDown( unsigned int key, bool bAlt )  OVERRIDE {}
    virtual void keyUp( unsigned int key, bool bAlt ) OVERRIDE {}
};


}
