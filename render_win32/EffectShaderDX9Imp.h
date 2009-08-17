#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderDX9 ) {
public: // from Shader
    virtual ShaderVariable * createVariable( wstring name ) OVERRIDE;
    virtual bool releaseShaderVariable( ShaderVariable * ) OVERRIDE;

public: // from EffectShader
    virtual bool setFloat( ShaderVariable * variable, float newValue ) OVERRIDE;
    virtual bool setFloatArray( ShaderVariable * variable, const float * newValues, size_t siz ) OVERRIDE;
    virtual bool setString( ShaderVariable * variable, wstring newValue ) OVERRIDE;

    virtual bool setTexture( ShaderVariable * variable, Texture * ) OVERRIDE;
    virtual bool setVertexShader( ShaderVariable * variable, VertexShader * ) OVERRIDE;
    virtual bool setPixelShader( ShaderVariable * variable, PixelShader * ) OVERRIDE;

    virtual bool isValidTechnique( ShaderVariable * techName ) OVERRIDE;

public: // from EffectShaderDX9
    virtual ShaderVariable * createTechniqueVariable( wstring name ) OVERRIDE;

    virtual bool setTechnique( ShaderVariable * variable ) OVERRIDE;

    virtual size_t begin() OVERRIDE;
    virtual void end() OVERRIDE;

    virtual void beginPass( size_t whichPass ) OVERRIDE;
    virtual void endPass() OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice, wstring filename );
    ~EffectShaderDX9Imp();

private:
    LPDIRECT3DDEVICE9 d3dDevice_;
    wstring filename_;
    LPD3DXEFFECT effect_;

    typedef list < ShaderVariableEffectDX9Ptr > ShaderVariables;
    ShaderVariables shaderVariables_;
};


};
