#pragma once
namespace my_render_win32_dx9_imp {


class RenderState_ZBufferDX9Imp : IMPLEMENTS_INTERFACE( RenderState_ZBufferDX9 ) {
public: // from RenderState_ZBufferDX9
    virtual void setEnable( bool ) OVERRIDE;
    virtual void setReadOnly( bool ) OVERRIDE;

    virtual void setCompare_Never() OVERRIDE;
    virtual void setCompare_Less() OVERRIDE;
    virtual void setCompare_Equal() OVERRIDE;
    virtual void setCompare_LessEqual() OVERRIDE;
    virtual void setCompare_Greater() OVERRIDE;
    virtual void setCompare_NotEqual() OVERRIDE;
    virtual void setCompare_GreaterEqual() OVERRIDE;
    virtual void setCompare_Always() OVERRIDE;

public:
    RenderState_ZBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device );

private:
    LPDIRECT3DDEVICE9 d3d9Device_;

};

}
