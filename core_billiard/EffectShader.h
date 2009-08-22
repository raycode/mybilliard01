#pragma once
namespace my_render {


MY_INTERFACE EffectShader : EXTENDS_INTERFACE( Shader ) {

    virtual bool renderWithTechnique( EffectShaderCallBack * calBack ) PURE;

    virtual EffectShaderVariableBlock * createVariableBlock( EffectShaderVariableBlockCallBack * ) PURE;
    virtual bool releaseShaderVariableBlock( EffectShaderVariableBlock * ) PURE;

};


}
