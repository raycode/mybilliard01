#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderDX9 ) {
public: // from Shader
    virtual size_t getNumberOfVariables() OVERRIDE;
    virtual ShaderVariable * createVariableByIndex( size_t index ) OVERRIDE;
    virtual ShaderVariable * createVariableByName( wstring name ) OVERRIDE;
    virtual ShaderVariable * createVariableBySemantic( wstring semantic ) OVERRIDE;
    virtual bool destroyShaderVariable( ShaderVariable * ) OVERRIDE;

    virtual bool hasVariableByName( wstring name ) OVERRIDE;
    virtual bool hasVariableBySemantic( wstring semantic ) OVERRIDE;

public: // from EffectShader
    virtual bool renderWithTechnique( EffectShaderCallBack * ) OVERRIDE;

    virtual EffectShaderVariableBlock * createVariableBlock( EffectShaderVariableBlockCallBack * ) OVERRIDE;
    virtual bool destroyShaderVariableBlock( EffectShaderVariableBlock * ) OVERRIDE;

    virtual EffectShaderVariable * createEffectVariableByIndex( size_t index ) OVERRIDE;
    virtual EffectShaderVariable * createEffectVariableByName( wstring name ) OVERRIDE;
    virtual EffectShaderVariable * createEffectVariableBySemantic( wstring semantic ) OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    EffectShaderDX9Imp( LPDIRECT3DDEVICE9 d3dDevice, wstring filename, LPD3DXEFFECTPOOL effectPool, RenderBufferFactory * renderFactory );

    wstring getFilename() const;

private: // acquire and release
    bool acquireBestValidTechnique();
    bool activateEffectVariable( ReleasableEffectResourceDX9 * var );
    bool destroyAnyEffectVariable( ReleasableEffectResourceDX9 * var );

private: // texture
    void acquireTextures();
    RenderBufferFactory * getRenderBufferFactory();

private:
    LPDIRECT3DDEVICE9 d3dDevice_;
    const wstring filename_;
    LPD3DXEFFECTPOOL effectPool_;
    RenderBufferFactory * const renderFactory_;

    MY_SMART_PTR( ID3DXEffect );
    ID3DXEffectPtr effect_;

    D3DXEFFECT_DESC effectDesc_;
    D3DXHANDLE bestTechnique_;

private: // variables
    typedef list < ReleasableEffectResourceDX9Ptr > EffectVariables;
    MY_SMART_PTR( EffectVariables );
    EffectVariablesPtr effectVariables_;

private: // texture
    typedef list< TexturePtr > BorrowedTextures;
    MY_SMART_PTR( BorrowedTextures );
    BorrowedTexturesPtr borrwoedTextures_;
};


};
