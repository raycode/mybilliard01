#pragma once
namespace my_render {


MY_INTERFACE KeyboardEventListener {
    virtual ~KeyboardEventListener() {}

    virtual void keyDown( unsigned int key, bool bAlt ) = 0;
    virtual void keyUp( unsigned int key, bool bAlt ) = 0;

};


}