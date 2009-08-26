#pragma once
namespace my_render_win32_dx9_imp {


class EffectShaderVariableDX9Imp : IMPLEMENTS_INTERFACE( EffectShaderVariableDX9 ) {
public: // from ShaderVariable
    virtual wstring getVariableName() OVERRIDE;
    virtual wstring getSemanticName() OVERRIDE;

    virtual bool isFloat() OVERRIDE;

    virtual bool isTexture() OVERRIDE;
    virtual bool isTexture1D() OVERRIDE;
    virtual bool isTexture2D() OVERRIDE;
    virtual bool isTexture3D() OVERRIDE;
    virtual bool isTextureCube() OVERRIDE;

    virtual bool isSampler() OVERRIDE;
    virtual bool isSampler1D() OVERRIDE;
    virtual bool isSampler2D() OVERRIDE;
    virtual bool isSampler3D() OVERRIDE;
    virtual bool isSamplerCube() OVERRIDE;

    virtual bool setFloat( float ) OVERRIDE;
    virtual bool setFloatArray( const float *, size_t count ) OVERRIDE;

    virtual bool setBool( bool ) OVERRIDE;
    virtual bool setBoolArray( const bool *, size_t count ) OVERRIDE;

    virtual bool setInt( int ) OVERRIDE;
    virtual bool setIntArray( const int *, size_t count ) OVERRIDE;

    virtual bool setString( wstring newValue ) OVERRIDE;

    virtual bool setTexture( Texture * ) OVERRIDE;

    virtual size_t getNumberOfNestedVariables() OVERRIDE;
    virtual ShaderVariable * createNestedVariableByIndex( size_t index ) OVERRIDE;
    virtual ShaderVariable * createNestedVariableByName( wstring name ) OVERRIDE;
    virtual ShaderVariable * createNestedVariableBySemantic( wstring semantic ) OVERRIDE;
    virtual bool destroyNestedVariable( ShaderVariable * nestedVariable ) OVERRIDE;

    virtual bool hasNestedVariableByName( wstring name ) OVERRIDE;
    virtual bool hasNestedVariableBySemantic( wstring semantic ) OVERRIDE;

public: // from EffectShaderVariable
    virtual size_t getNumberOfAnnotations() OVERRIDE;
    virtual EffectShaderAnnotation * createAnnotationByIndex( size_t index ) OVERRIDE;
    virtual EffectShaderAnnotation * createAnnotationByName( wstring name ) OVERRIDE;
    virtual bool destroyShaderAnnotation( EffectShaderAnnotation * ) OVERRIDE;

    virtual bool hasAnnotationByName( wstring name ) OVERRIDE;

    virtual bool isShared() OVERRIDE;

public: // from ShaderVariableHandleDX9
    virtual D3DXHANDLE getHandleDX9() OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public: // from ReleasableEffectResourceDX9
    virtual void setEffect( LPD3DXEFFECT effect ) OVERRIDE;

public:
    enum ESEARCH_BY { ESEARCH_BY_INDEX, ESEARCH_BY_NAME, ESEARCH_BY_SEMANTIC };
    EffectShaderVariableDX9Imp( ESEARCH_BY, wstring nameOrSemantic, ShaderVariableHandleDX9 * parent );
    EffectShaderVariableDX9Imp( ESEARCH_BY, size_t index, ShaderVariableHandleDX9 * parent );

private:
    bool activateNestedVariable( ReleasableEffectResourceDX9 * var );
    bool destroyAnyEffectVariable( ReleasableEffectResourceDX9 * var );
    D3DXHANDLE getParentHandleDX9();
    const D3DXPARAMETER_DESC & getParameterDesc();

private: // input
    const ESEARCH_BY searchBy_;
    const wstring nameOrSemantic_;
    const size_t variableIndex_;
    ShaderVariableHandleDX9 * const parent_;
    LPD3DXEFFECT effect_;

private:
    D3DXPARAMETER_DESC desc_;
    D3DXHANDLE handle_;

    typedef list < ReleasableEffectResourceDX9Ptr > NestedVariables;
    NestedVariables nestedVariables_;
};


}