#pragma once
namespace my_render {


MY_INTERFACE Shader {
    virtual ~Shader() {}

    virtual size_t getNumberOfVariables() PURE;

    virtual ShaderVariable * createVariableByIndex( size_t index ) PURE;
    virtual ShaderVariable * createVariableByName( wstring name ) PURE;
    virtual ShaderVariable * createVariableBySemantic( wstring semantic ) PURE;
    virtual bool releaseShaderVariable( ShaderVariable * ) PURE;

};


}