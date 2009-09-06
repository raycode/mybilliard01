#pragma once
namespace my_render {


MY_INTERFACE EffectShaderFeeder {
    virtual ~EffectShaderFeeder() {}

    virtual void setEffectShader( EffectShader * ) PURE;
    virtual EffectShader * getEffectShader() PURE;

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) PURE;

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) PURE;

};

}

