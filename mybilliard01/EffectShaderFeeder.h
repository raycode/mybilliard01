#pragma once


MY_INTERFACE EffectShaderFeeder {
    virtual ~EffectShaderFeeder() {}

    virtual void display() PURE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

