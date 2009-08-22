#pragma once
namespace my_render {


MY_INTERFACE EffectShaderCallBack {
    virtual ~EffectShaderCallBack() {}

    virtual void displayPass( size_t pass ) PURE;

};


}
