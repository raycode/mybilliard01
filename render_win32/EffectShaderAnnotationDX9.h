#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderAnnotationDX9
    : EXTENDS_INTERFACE( EffectShaderAnnotation )
    , EXTENDS_INTERFACE( ShaderVariableHandleDX9 )
    , EXTENDS_INTERFACE( ReleasableEffectResourceDX9 )
{

};


}