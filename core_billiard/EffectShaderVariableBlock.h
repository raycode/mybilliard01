#pragma once
namespace my_render {


MY_INTERFACE EffectShaderVariableBlock {
    virtual ~EffectShaderVariableBlock() {}

    virtual void applyNow() PURE;

    virtual EffectShader * getEffectShader() PURE;

};


}