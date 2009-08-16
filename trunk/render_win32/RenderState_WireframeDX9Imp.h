#pragma once
namespace my_render_win32_dx9_imp {


class RenderState_WireframeDX9Imp : IMPLEMENTS_( RenderState_WireframeDX9 ) {
public: // from RenderState_Wireframe
    virtual void setSolid() OVERRIDE;
    virtual void setWired() OVERRIDE;

    virtual bool isSolid() const OVERRIDE;

public:
    RenderState_WireframeDX9Imp( LPDIRECT3DDEVICE9 d3d9Device );

private:
    volatile LPDIRECT3DDEVICE9 d3d9Device_;

};


}