#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ReleasableEffectResourceDX9 : EXTENDS_INTERFACE( ReleasableResourceDX9 ) {

    virtual void setEffect( LPD3DXEFFECT effect ) PURE;

};


}