#pragma once
namespace my_render {


MY_INTERFACE EffectShaderVariableBlockCallBack {
    virtual ~EffectShaderVariableBlockCallBack() {}

    virtual void setEffectShaderVariableBlock() PURE;

};


}