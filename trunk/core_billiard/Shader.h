#pragma once
namespace my_render {


MY_INTERFACE Shader {
    virtual ~Shader() {}

    virtual ShaderVariable * createVariable( wstring name ) PURE;
    virtual bool releaseShaderVariable( ShaderVariable * ) PURE;

};


}