#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderVariableDX9
    : EXTENDS_INTERFACE( ShaderVariableDX9 )
    , EXTENDS_INTERFACE( EffectShaderVariable )
    , EXTENDS_INTERFACE( ReleasableEffectResourceDX9 )
{

};


}