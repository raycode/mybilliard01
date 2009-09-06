#pragma once
namespace my_render {


NULL_OBJECT( EffectShaderFeeder ) {

    virtual void setEffectShader( EffectShader * ) OVERRIDE {}
    virtual EffectShader * getEffectShader() OVERRIDE { return NULL; }

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE {}

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) OVERRIDE { return false; }


};

}
