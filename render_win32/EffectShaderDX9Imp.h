#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderDX9 ) {
public: // from Shader
    virtual size_t getNumberOfVariables() OVERRIDE;
    virtual ShaderVariable * createVariableByIndex( size_t index ) OVERRIDE;
    virtual ShaderVariable * createVariableByName( wstring name ) OVERRIDE;
    virtual ShaderVariable * createVariableBySemantic( wstring semantic ) OVERRIDE;
    virtual bool releaseShaderVariable( ShaderVariable * ) OVERRIDE;

public: // from EffectShader
    virtual bool renderWithTechnique( EffectShaderCallBack * ) OVERRIDE;

    virtual EffectShaderVariableBlock * createVariableBlock( EffectShaderVariableBlockCallBack * ) OVERRIDE;
    virtual bool releaseShaderVariableBlock( EffectShaderVariableBlock * ) OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice, wstring filename, LPD3DXEFFECTPOOL effectPool );

    wstring getFilename() const;

private: // acquire and release
    bool acquireBestValidTechnique();
    void setEffectOntoEffectVariable( ReleasableEffectResourceDX9 * var );
    bool releaseAnyEffectVariable( ReleasableEffectResourceDX9 * var );

private:
    LPDIRECT3DDEVICE9 d3dDevice_;
    LPD3DXEFFECTPOOL effectPool_;
    const wstring filename_;

    MY_SMART_PTR( ID3DXEffect );
    ID3DXEffectPtr effect_;

    D3DXEFFECT_DESC effectDesc_;
    D3DXHANDLE bestTechnique_;

    typedef list < ReleasableEffectResourceDX9Ptr > EffectVariables;
    MY_SMART_PTR( EffectVariables );
    EffectVariablesPtr effectVariables_;

};


};
