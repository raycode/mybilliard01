#pragma once
namespace my_render {


MY_INTERFACE PixelShader
    : EXTENDS_INTERFACE_( Shader )
    , EXTENDS_INTERFACE_( ShaderVariableWriter )
{

    virtual void setSampler(
        ShaderVariable * variable,
        Texture * texture,
        Texture::FilterType magFilter,
        Texture::FilterType minFilter,
        Texture::FilterType mapFilter ) = 0;

};


}