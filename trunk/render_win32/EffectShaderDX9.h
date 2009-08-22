#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderDX9
    : EXTENDS_INTERFACE( EffectShader )
    , EXTENDS_INTERFACE( ReleasableResourceDX9 )
{

};


}