#pragma once
namespace my_render {


MY_INTERFACE EffectShaderAnnotation {
    virtual ~EffectShaderAnnotation() {}

    virtual void getValue( void * dest, size_t sizeInByte ) PURE;

    virtual wstring getAnnotationName() PURE;

};


}