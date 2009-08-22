#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderVariableBlockDX9
    : EXTENDS_INTERFACE( EffectShaderVariableBlock )
    , EXTENDS_INTERFACE( ShaderVariableHandleDX9 )
    , EXTENDS_INTERFACE( ReleasableEffectResourceDX9 )
{

};


}