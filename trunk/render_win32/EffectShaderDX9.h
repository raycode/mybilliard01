#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderDX9 : EXTENDS_INTERFACE_STATIC_( EffectShader ) {

    virtual bool createEffectFromFile( wstring filename ) = 0;

    virtual bool setTechnique( ShaderVariable * variable ) = 0;

    virtual size_t begin() = 0;
    virtual void end() = 0;
    virtual void pass( size_t whichPass ) = 0;
};


}