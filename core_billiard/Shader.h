#pragma once
namespace my_render {


MY_INTERFACE Shader {
    virtual ~Shader() {}

    virtual size_t getNumberOfVariables() PURE;

    virtual ShaderVariable * createVariableByIndex( size_t index ) PURE;
    virtual ShaderVariable * createVariableByName( wstring name ) PURE;
    virtual ShaderVariable * createVariableBySemantic( wstring semantic ) PURE;
    virtual bool releaseShaderVariable( ShaderVariable * ) PURE;

    virtual bool hasVariableByName( wstring name ) PURE;
    virtual bool hasVariableBySemantic( wstring semantic ) PURE;


public: // releaser

    struct Releaser {
    public:
        void operator()( ShaderVariable * shaderVariable ) {
            owner_->releaseShaderVariable( shaderVariable );
        }

    public: Releaser( Shader * owner ) : owner_( owner ) {}
    private: Shader * const owner_;
    };

};


}