#pragma once
namespace my_render {


MY_INTERFACE PixelShader
    : EXTENDS_INTERFACE( Shader )
    , EXTENDS_INTERFACE( ShaderVariableWriter )
{

    virtual void setSampler(
        ShaderVariable * variable,
        Texture * texture,
        Texture::FilterType magFilter,
        Texture::FilterType minFilter,
        Texture::FilterType mapFilter ) = 0;

};


}