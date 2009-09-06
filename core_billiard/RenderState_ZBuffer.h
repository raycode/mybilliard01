#pragma once
namespace my_render {


MY_INTERFACE RenderState_ZBuffer {
    virtual ~RenderState_ZBuffer() {}

    virtual void setEnable( bool ) PURE;
    virtual void setReadOnly( bool ) PURE;

    virtual void setCompare_Never() PURE;
    virtual void setCompare_Less() PURE;
    virtual void setCompare_Equal() PURE;
    virtual void setCompare_LessEqual() PURE;
    virtual void setCompare_Greater() PURE;
    virtual void setCompare_NotEqual() PURE;
    virtual void setCompare_GreaterEqual() PURE;
    virtual void setCompare_Always() PURE;

};

}
