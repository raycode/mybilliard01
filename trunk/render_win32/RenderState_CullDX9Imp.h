#pragma once
namespace my_render_win32_dx9_imp {


class RenderState_CullDX9Imp : IMPLEMENTS_INTERFACE( RenderState_CullDX9 ) {
public: // from RenderState_Wireframe
    virtual void setNone() OVERRIDE;
    virtual void setClockWise() OVERRIDE;
    virtual void setCounterClockWise() OVERRIDE;

public:
    RenderState_CullDX9Imp( LPDIRECT3DDEVICE9 d3d9Device );

private:
    volatile LPDIRECT3DDEVICE9 d3d9Device_;

};


}