#pragma once
namespace my_render {


MY_INTERFACE EffectShaderCameraFeeder {
    virtual ~EffectShaderCameraFeeder() {}

    virtual void updateProjection_camera( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateView_camera(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

}

