#pragma once
namespace my_render {


NULL_OBJECT( ShaderVariable ) {

    virtual wstring getVariableName() OVERRIDE { return L""; }
    virtual wstring getSemanticName() OVERRIDE { return L""; }

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
    virtual bool releaseNestedVariable( ShaderVariable * nestedVariable ) OVERRIDE { return false; }

};


}