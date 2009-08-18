#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ShaderVariableEffectDX9 : STATIC_EXTENDS_INTERFACE( ShaderVariableDX9 ) {

    virtual void setEffect( LPD3DXEFFECT effect ) PURE;

};


}