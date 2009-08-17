#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderDX9 : STATIC_EXTENDS_INTERFACE( EffectShader ), EXTENDS_INTERFACE( ReleasableResourceDX9 ) {

    virtual bool setTechnique( ShaderVariable * variable ) = 0;

    virtual size_t begin() = 0;
    virtual void end() = 0;

    virtual void beginPass( size_t whichPass ) = 0;
    virtual void endPass() = 0;
};


}