#pragma once


MY_INTERFACE SharedEffectVariableFeeder {
    virtual ~SharedEffectVariableFeeder() {}


    virtual void updateProjection( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

