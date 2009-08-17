#pragma once
namespace my_render {


MY_INTERFACE EffectShader : EXTENDS_INTERFACE( Shader ) {

    virtual ShaderVariable * createTechniqueVariable( wstring name ) = 0;

    virtual bool setFloat( ShaderVariable * variable, float ) = 0;
    virtual bool setFloatArray( ShaderVariable * variable, const float *, size_t siz ) = 0;
    virtual bool setString( ShaderVariable * variable, wstring newValue ) = 0;

    virtual bool setTexture( ShaderVariable * variable, Texture * ) = 0;
    virtual bool setVertexShader( ShaderVariable * variable, VertexShader * ) = 0;
    virtual bool setPixelShader( ShaderVariable * variable, PixelShader * ) = 0;

    virtual bool isValidTechnique( ShaderVariable * techName ) = 0;

};


}