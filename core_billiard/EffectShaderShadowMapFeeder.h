#pragma once
namespace my_render {


MY_INTERFACE EffectShaderShadowMapFeeder {
    virtual ~EffectShaderShadowMapFeeder() {}

    virtual void updateProjection_shadowMap( size_t index, const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateView_shadowMap(
        size_t index,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

}

