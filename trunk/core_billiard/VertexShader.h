#pragma once
namespace my_render {


INTERFACE_ VertexShader
    : EXTENDS_INTERFACE_( Shader )
    , EXTENDS_INTERFACE_( ShaderVariableWriter )
{
public:

public: virtual ~VertexShader() {}
};


}