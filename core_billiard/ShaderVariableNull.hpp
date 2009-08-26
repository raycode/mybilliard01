#pragma once
namespace my_render {


NULL_OBJECT( ShaderVariable ) {

    virtual wstring getVariableName() OVERRIDE { return L""; }
    virtual wstring getSemanticName() OVERRIDE { return L""; }

    virtual bool isFloat() OVERRIDE { return false; }

    virtual bool isTexture() OVERRIDE { return false; }
    virtual bool isTexture1D() OVERRIDE { return false; }
    virtual bool isTexture2D() OVERRIDE { return false; }
    virtual bool isTexture3D() OVERRIDE { return false; }
    virtual bool isTextureCube() OVERRIDE { return false; }

    virtual bool isSampler() OVERRIDE { return false; }
    virtual bool isSampler1D() OVERRIDE { return false; }
    virtual bool isSampler2D() OVERRIDE { return false; }
    virtual bool isSampler3D() OVERRIDE { return false; }
    virtual bool isSamplerCube() OVERRIDE { return false; }

    virtual bool setFloat( float ) OVERRIDE { return false; }
    virtual bool setFloatArray( const float *, size_t count ) OVERRIDE { return false; }

    virtual bool setBool( bool ) OVERRIDE { return false; }
    virtual bool setBoolArray( const bool *, size_t count ) OVERRIDE { return false; }

    virtual bool setInt( int ) OVERRIDE { return false; }
    virtual bool setIntArray( const int *, size_t count ) OVERRIDE { return false; }

    virtual bool setString( wstring newValue ) OVERRIDE { return false; }

    virtual bool setTexture( Texture * ) OVERRIDE { return false; }

    virtual size_t getNumberOfNestedVariables() OVERRIDE { return 0u; }
    virtual ShaderVariable * createNestedVariableByIndex( size_t index ) OVERRIDE { return this; }
    virtual ShaderVariable * createNestedVariableByName( wstring name ) OVERRIDE { return this; }
    virtual ShaderVariable * createNestedVariableBySemantic( wstring semantic ) OVERRIDE { return this; }
    virtual bool destroyNestedVariable( ShaderVariable * nestedVariable ) OVERRIDE { return false; }

    virtual bool hasNestedVariableByName( wstring name ) OVERRIDE { return false; }
    virtual bool hasNestedVariableBySemantic( wstring semantic ) OVERRIDE { return false; }

};


}