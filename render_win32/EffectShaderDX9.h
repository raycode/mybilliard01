#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ EffectShaderDX9 : EXTENDS_INTERFACE_STATIC_( EffectShader ) {
public:
    virtual HRESULT createEffectFromFile( wstring filename ) = 0;

    virtual ShaderVariable * createTechniqueVariable( wstring name ) = 0;

    virtual bool setTechnique( ShaderVariable * variable ) = 0;
};


}