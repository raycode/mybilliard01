#pragma once
namespace my_render {


INTERFACE_ EffectShader : EXTENDS_INTERFACE_( Shader ) {
public:
    virtual void setFloat( wstring variable, float ) = 0;
    virtual void setFloatArray( wstring variable, const float *, size_t siz ) = 0;
    virtual void setString( wstring variable, wstring newValue ) = 0;

    virtual void setTexture( wstring variable, Texture * ) = 0;
    virtual void setVertexShader( wstring variable, VertexShader * ) = 0;
    virtual void setPixelShader( wstring variable, PixelShader * ) = 0;

    virtual bool isValidTechnique( wstring techName ) = 0;

public: virtual ~EffectShader() {}
};


}