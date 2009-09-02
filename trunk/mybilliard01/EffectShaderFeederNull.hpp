#pragma once


NULL_OBJECT( EffectShaderFeeder ) {

    void display() OVERRIDE {}

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE {}

    virtual void updateCameraMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matWorld,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE {}

    virtual void updateMatrix(
        wstring variableName,
        const RowMajorMatrix44f & matValue ) OVERRIDE {}

};

