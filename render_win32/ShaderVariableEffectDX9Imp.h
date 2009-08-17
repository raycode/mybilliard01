#pragma once
namespace my_render_win32_dx9_imp {


class ShaderVariableEffectDX9Imp : IMPLEMENTS_INTERFACE( ShaderVariableEffectDX9 ) {
public: // from ShaderVariable
    virtual wstring getVariableName() OVERRIDE;

public: // from ShaderVariableDX9
    virtual D3DXHANDLE getHandleDX9() OVERRIDE;

public: // from ShaderVariableEffectDX9
    virtual void setEffect( LPD3DXEFFECT effect ) OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    enum EVARIABLETYPE { ETYPE_TECHNIQUE, ETYPE_PARAM, ETYPE_VERTEX_SHADER, ETYPE_PIXEL_SHADER };
    ShaderVariableEffectDX9Imp( wstring variableName, EVARIABLETYPE variableType );
    ~ShaderVariableEffectDX9Imp();

private: // input
    wstring variableName_;
    EVARIABLETYPE variableType_;
    LPD3DXEFFECT effect_;

private: // output
    D3DXHANDLE handle_;
};


}