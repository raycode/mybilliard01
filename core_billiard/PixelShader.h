#pragma once
namespace my_render {


INTERFACE_ PixelShader
    : EXTENDS_INTERFACE_( Shader )
    , EXTENDS_INTERFACE_( ShaderVariableWriter )
{
public:
    virtual void setSampler(
        wstring variableName,
        Texture * texture,
        Texture::FilterType magFilter,
        Texture::FilterType minFilter,
        Texture::FilterType mapFilter ) = 0;

public: virtual ~PixelShader() {}
};


}