#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderAnnotationDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderAnnotationDX9 ) {
public: // from ShaderAnnotation
    virtual void getValue( void * dest, size_t sizeInByte ) OVERRIDE;
    virtual wstring getAnnotationName() OVERRIDE;

public: // from ShaderVariableHandleDX9
    virtual D3DXHANDLE getHandleDX9() OVERRIDE;

public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public: // from ReleasableEffectResourceDX9
    virtual void setEffect( LPD3DXEFFECT effect ) OVERRIDE;

public:
    EffectShaderAnnotationDX9Imp( size_t index, EffectShaderVariableDX9 * parent );
    EffectShaderAnnotationDX9Imp( wstring name, EffectShaderVariableDX9 * parent );
    ~EffectShaderAnnotationDX9Imp();

private:
    D3DXHANDLE getParentHandle();

private:
    enum ESEARCH_BY { ESEARCH_BY_INDEX, ESEARCH_BY_NAME };
    const ESEARCH_BY searchBy_;
    const size_t index_;
    const wstring name_;
    EffectShaderVariableDX9 * const parent_;

    LPD3DXEFFECT effect_;

private:
    D3DXHANDLE handle_;

};


}