#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderVariableBlockDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderVariableBlockDX9 ) {
public: // from EffectShaderVariableBlock
    virtual void applyNow() OVERRIDE;
    virtual EffectShader * getEffectShader() OVERRIDE;

public: // from ShaderVariableHandleDX9
    virtual D3DXHANDLE getHandleDX9() OVERRIDE;

public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public: // from ReleasableEffectResourceDX9
    virtual void setEffect( LPD3DXEFFECT effect ) OVERRIDE;

public:
    EffectShaderVariableBlockDX9Imp( EffectShader * parent, EffectShaderVariableBlockCallBack * callBack );
    ~EffectShaderVariableBlockDX9Imp();

private:
    EffectShader * const parent_;
    EffectShaderVariableBlockCallBack * const callBack_;
    LPD3DXEFFECT effect_;

private:
    D3DXHANDLE handle_;
};


}