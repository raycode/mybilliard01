#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ShaderVariableDX9
    : EXTENDS_INTERFACE( ShaderVariable )
    , EXTENDS_INTERFACE( ShaderVariableHandleDX9 )
    , EXTENDS_INTERFACE( ReleasableResourceDX9 )
{

};


}