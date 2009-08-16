#pragma once
namespace my_render {


MY_INTERFACE Shader {
    virtual ~Shader() {}

    virtual ShaderVariable * createVariable( wstring name ) = 0;
    virtual bool releaseShaderVariable( ShaderVariable * ) = 0;

};


}