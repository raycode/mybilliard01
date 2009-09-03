#pragma once


class GlobalEffectShaderFeeder {
public:
    virtual void displayWithEffect( const RowMajorMatrix44f & matWorld ) PURE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

