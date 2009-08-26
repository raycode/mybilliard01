#pragma once


MY_INTERFACE EffectShaderFeeder : EXTENDS_INTERFACE( EffectShaderCallBack )
{

    virtual void display() PURE;

    virtual void updateMatrix(
        NxActor *,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matProj,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) PURE;

};

