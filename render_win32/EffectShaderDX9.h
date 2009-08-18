#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE EffectShaderDX9 : STATIC_EXTENDS_INTERFACE( EffectShader ), EXTENDS_INTERFACE( ReleasableResourceDX9 ) {

    virtual bool setTechnique( ShaderVariable * variable ) PURE;

    virtual size_t begin() PURE;
    virtual void end() PURE;

    virtual void beginPass( size_t whichPass ) PURE;
    virtual void endPass() PURE;
};


}