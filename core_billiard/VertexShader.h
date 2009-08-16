#pragma once
namespace my_render {


MY_INTERFACE VertexShader
    : EXTENDS_INTERFACE_( Shader )
    , EXTENDS_INTERFACE_( ShaderVariableWriter )
{

};


}