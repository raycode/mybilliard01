#pragma once
namespace my_render {


MY_INTERFACE EffectShaderVariable : EXTENDS_INTERFACE( ShaderVariable ) {

    virtual size_t getNumberOfAnnotations() PURE;
    virtual EffectShaderAnnotation * createAnnotationByIndex( size_t index ) PURE;
    virtual EffectShaderAnnotation * createAnnotationByName( wstring name ) PURE;
    virtual bool releaseShaderAnnotation( EffectShaderAnnotation * ) PURE;

    virtual bool hasAnnotationByName( wstring name ) PURE;

    virtual bool isShared() PURE;

public: // releaser

    struct Releaser {
    public:
        void operator()( EffectShaderAnnotation * anno ) {
            owner_->releaseShaderAnnotation( anno );
        }

    public: Releaser( EffectShaderVariable * owner ) : owner_( owner ) {}
    private: EffectShaderVariable * const owner_;
    };

};


}