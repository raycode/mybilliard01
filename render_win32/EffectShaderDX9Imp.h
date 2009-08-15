#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderDX9Imp : IMPLEMENTS_( EffectShaderDX9 ) {
public: // from EffectShader
    virtual bool setFloat( ShaderVariable * variable, float newValue ) OVERRIDE;
    virtual bool setFloatArray( ShaderVariable * variable, const float * newValues, size_t siz ) OVERRIDE;
    virtual bool setString( ShaderVariable * variable, wstring newValue ) OVERRIDE;

    virtual bool setTexture( ShaderVariable * variable, Texture * ) OVERRIDE;
    virtual bool setVertexShader( ShaderVariable * variable, VertexShader * ) OVERRIDE;
    virtual bool setPixelShader( ShaderVariable * variable, PixelShader * ) OVERRIDE;

    virtual bool isValidTechnique( ShaderVariable * techName ) OVERRIDE;

public: // from Shader
    virtual ShaderVariable * createVariable( wstring name ) OVERRIDE;
    virtual bool releaseShaderVariable( ShaderVariable * ) OVERRIDE;

public: // from EffectShaderDX9
    virtual HRESULT createEffectFromFile( wstring filename ) OVERRIDE;

    virtual ShaderVariable * createTechniqueVariable( wstring name ) OVERRIDE;

    virtual bool setTechnique( ShaderVariable * variable ) OVERRIDE;

public:
    EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice );

private:
    D3DXHANDLE getParameterByName( wstring name );
    D3DXHANDLE getTechniqueByName( wstring name );

private:
    LPDIRECT3DDEVICE9 d3dDevice_;
    ID3DXEffect * effect_;

    typedef list < ShaderVariablePtr > ShaderVariables;
    ShaderVariables shaderVariables_;

private:
    wstring filename_;
};

};