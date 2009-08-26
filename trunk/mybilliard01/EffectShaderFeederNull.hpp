#pragma once


NULL_OBJECT( EffectShaderFeeder ) {

    void display() OVERRIDE {}

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE {}

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE {};

};

