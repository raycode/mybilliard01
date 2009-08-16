#pragma once
namespace my_render {


NULL_OBJECT( KeyboardEventListener ) {

    virtual void keyDown( unsigned int key, bool bAlt )  OVERRIDE {}
    virtual void keyUp( unsigned int key, bool bAlt ) OVERRIDE {}
};


}
