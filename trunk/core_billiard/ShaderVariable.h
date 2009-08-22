#pragma once
namespace my_render {


MY_INTERFACE ShaderVariable {
    virtual ~ShaderVariable() {}
    
    virtual wstring getVariableName() PURE;
    virtual wstring getSemanticName() PURE;

    virtual bool setFloat( float ) PURE;
    virtual bool setFloatArray( const float *, size_t count ) PURE;

    virtual bool setBool( bool ) PURE;
    virtual bool setBoolArray( const bool *, size_t count ) PURE;

    virtual bool setInt( int ) PURE;
    virtual bool setIntArray( const int *, size_t count ) PURE;

    virtual bool setString( wstring newValue ) PURE;

    // TODO
    virtual bool setTexture( Texture * ) PURE;
    virtual bool setSampler() PURE;

    virtual size_t getNumberOfNestedVariables() PURE;
    virtual ShaderVariable * createNestedVariableByIndex( size_t index ) PURE;
    virtual ShaderVariable * createNestedVariableByName( wstring name ) PURE;
    virtual ShaderVariable * createNestedVariableBySemantic( wstring semantic ) PURE;
    virtual bool releaseNestedVariable( ShaderVariable * nestedVariable ) PURE;

};


}