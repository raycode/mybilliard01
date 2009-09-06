#pragma once
namespace my_render {


NULL_OBJECT( RenderState_ZBuffer ) {

    virtual void setEnable( bool ) OVERRIDE {}
    virtual void setReadOnly( bool ) OVERRIDE {}

    virtual void setCompare_Never() OVERRIDE {}
    virtual void setCompare_Less() OVERRIDE {}
    virtual void setCompare_Equal() OVERRIDE {}
    virtual void setCompare_LessEqual() OVERRIDE {}
    virtual void setCompare_Greater() OVERRIDE {}
    virtual void setCompare_NotEqual() OVERRIDE {}
    virtual void setCompare_GreaterEqual() OVERRIDE {}
    virtual void setCompare_Always() OVERRIDE {}

};

}