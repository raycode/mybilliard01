#pragma once
namespace my_render_win32_dx9_imp {


class RenderState_AlphaDX9Imp : IMPLEMENTS_INTERFACE( RenderState_AlphaDX9 ) {
public: // from RenderState_AlphaDX9
    virtual void setColorBufferTurnOff() OVERRIDE;
    virtual void setColorBufferTurnOn() OVERRIDE;

public:
    RenderState_AlphaDX9Imp( LPDIRECT3DDEVICE9 d3d9Device );

private:
    LPDIRECT3DDEVICE9 d3d9Device_;

};

}
