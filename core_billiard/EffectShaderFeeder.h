#pragma once
namespace my_render {


MY_INTERFACE EffectShaderFeeder {
    virtual ~EffectShaderFeeder() {}

    virtual void setEffectShader( EffectShader * ) PURE;
    virtual EffectShader * getEffectShader() PURE;

    virtual void updateCameraProjection( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) PURE;

    virtual bool displayWithEffect( EffectShaderCallBack * calBack ) PURE;

};

}

