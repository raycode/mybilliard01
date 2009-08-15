#pragma once
namespace my_render {


INTERFACE_ Shader {
public:
    virtual ShaderVariable * createVariable( wstring name ) = 0;
    virtual bool releaseShaderVariable( ShaderVariable * ) = 0;

public: virtual ~Shader() {}
};


}