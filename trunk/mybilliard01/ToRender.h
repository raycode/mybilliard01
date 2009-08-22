#pragma once


MY_INTERFACE ToRender
    : EXTENDS_INTERFACE( EffectShaderVariableBlockCallBack )
    , EXTENDS_INTERFACE( EffectShaderCallBack )
{

    virtual void updateMatrix( NxActor *, const RowMajorMatrix44f & matView, const RowMajorMatrix44f & matProjView ) PURE;

    virtual void display() PURE;

};

