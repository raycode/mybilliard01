#pragma once


class ShadowMapEffectShaderFeeder : IMPLEMENTS_INTERFACE( GlobalEffectShaderFeeder ) {
public:
    virtual void display( NxActor * ) OVERRIDE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateMatrix(
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public:
    ShadowMapEffectShaderFeeder();

private:

};

