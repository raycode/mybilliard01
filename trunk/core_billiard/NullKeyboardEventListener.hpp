#pragma once
namespace my_render {


class NullKeyboardEventListener : IMPLEMENTS_( KeyboardEventListener ) {
public:
    virtual void keyDown( unsigned int key, bool bAlt ) {}
    virtual void keyUp( unsigned int key, bool bAlt ) {}
};


}
