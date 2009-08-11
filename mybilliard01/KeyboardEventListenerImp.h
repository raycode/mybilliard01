#pragma once
namespace my_render_d3d9_imp {


class KeyboardEventListenerImp : IMPLEMENTS_( KeyboardEventListener ) {
public:
    virtual void keyDown( unsigned int key, bool bAlt );
    virtual void keyUp( unsigned int key, bool bAlt );

};


}
