#pragma once
namespace my_render {


MY_INTERFACE EffectShader : EXTENDS_INTERFACE( Shader ) {

    virtual bool renderWithTechnique( EffectShaderCallBack * calBack ) PURE;

    virtual EffectShaderVariableBlock * createVariableBlock( EffectShaderVariableBlockCallBack * ) PURE;
    virtual bool destroyShaderVariableBlock( EffectShaderVariableBlock * ) PURE;

    virtual EffectShaderVariable * createEffectVariableByIndex( size_t index ) PURE;
    virtual EffectShaderVariable * createEffectVariableByName( wstring name ) PURE;
    virtual EffectShaderVariable * createEffectVariableBySemantic( wstring semantic ) PURE;
};


}
