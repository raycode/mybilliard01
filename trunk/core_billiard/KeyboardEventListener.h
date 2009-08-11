#pragma once
namespace my_render {


INTERFACE_ KeyboardEventListener {
public:
    virtual void keyDown( unsigned int key, bool bAlt ) = 0;
    virtual void keyUp( unsigned int key, bool bAlt ) = 0;

public: virtual ~KeyboardEventListener() {}
};


}