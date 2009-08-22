#pragma once
namespace my_render {


MY_INTERFACE EffectShaderVariable : EXTENDS_INTERFACE( ShaderVariable ) {

    virtual size_t getNumberOfAnnotations() PURE;
    virtual EffectShaderAnnotation * createAnnotationByIndex( size_t index ) PURE;
    virtual EffectShaderAnnotation * createAnnotationByName( wstring name ) PURE;
    virtual bool releaseShaderAnnotation( EffectShaderAnnotation * ) PURE;

};


}