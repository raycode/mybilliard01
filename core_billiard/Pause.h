#pragma once
namespace my_render {


INTERFACE_ Pause {
public: // from Pause
    virtual void setPause( bool ) = 0;
    virtual void isPaused() = 0;
};


}

