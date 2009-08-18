#pragma once
namespace my_render {


MY_INTERFACE EffectShader : EXTENDS_INTERFACE( Shader ) {

    virtual ShaderVariable * createTechniqueVariable( wstring name ) PURE;

    virtual bool setFloat( ShaderVariable * variable, float ) PURE;
    virtual bool setFloatArray( ShaderVariable * variable, const float *, size_t siz ) PURE;
    virtual bool setString( ShaderVariable * variable, wstring newValue ) PURE;

    virtual bool setTexture( ShaderVariable * variable, Texture * ) PURE;
    virtual bool setVertexShader( ShaderVariable * variable, VertexShader * ) PURE;
    virtual bool setPixelShader( ShaderVariable * variable, PixelShader * ) PURE;

    virtual bool isValidTechnique( ShaderVariable * techName ) PURE;

};


}