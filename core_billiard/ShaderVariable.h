#pragma once
namespace my_render {


MY_INTERFACE ShaderVariable {
    virtual ~ShaderVariable() {}
    
    virtual wstring getVariableName() PURE;
    virtual wstring getSemanticName() PURE;

    virtual bool isFloat() PURE;
    
    virtual bool isTexture() PURE;
    virtual bool isTexture1D() PURE;
    virtual bool isTexture2D() PURE;
    virtual bool isTexture3D() PURE;
    virtual bool isTextureCube() PURE;

    virtual bool isSampler() PURE;
    virtual bool isSampler1D() PURE;
    virtual bool isSampler2D() PURE;
    virtual bool isSampler3D() PURE;
    virtual bool isSamplerCube() PURE;

    virtual bool setFloat( float ) PURE;
    virtual bool setFloatArray( const float *, size_t count ) PURE;

    virtual bool setBool( bool ) PURE;
    virtual bool setBoolArray( const bool *, size_t count ) PURE;

    virtual bool setInt( int ) PURE;
    virtual bool setIntArray( const int *, size_t count ) PURE;

    virtual bool setString( wstring newValue ) PURE;

    virtual bool setTexture( Texture * ) PURE;

    virtual size_t getNumberOfNestedVariables() PURE;
    virtual ShaderVariable * createNestedVariableByIndex( size_t index ) PURE;
    virtual ShaderVariable * createNestedVariableByName( wstring name ) PURE;
    virtual ShaderVariable * createNestedVariableBySemantic( wstring semantic ) PURE;
    virtual bool destroyNestedVariable( ShaderVariable * nestedVariable ) PURE;

    virtual bool hasNestedVariableByName( wstring name ) PURE;
    virtual bool hasNestedVariableBySemantic( wstring semantic ) PURE;

};


}