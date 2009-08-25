#pragma once
namespace my_render {


MY_INTERFACE EffectShaderAnnotation {
    virtual ~EffectShaderAnnotation() {}

    virtual wstring getAnnotationName() PURE;

    virtual bool isString() PURE;
    virtual bool isFloat() PURE;
    virtual bool isBool() PURE;

    virtual wstring getString() PURE;
    virtual float getFloat() PURE;
    virtual bool getBool() PURE;

};


}