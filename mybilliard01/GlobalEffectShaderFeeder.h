#pragma once

class GlobalEffectShaderFeeder {
public:
    virtual void display( NxActor * ) PURE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) PURE;

    virtual void updateMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

