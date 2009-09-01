#pragma once


class ShadowMapEffectShaderFeeder
    : IMPLEMENTS_INTERFACE( GlobalEffectShaderFeeder )
{
public: // from GlobalEffectShaderFeeder
    virtual void display( NxActor * ) OVERRIDE;

    virtual void updateProjection( const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateMatrix(
        const NxVec3 & lightPos,
        const NxVec3 & lightDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public:
    ShadowMapEffectShaderFeeder( EffectShader * );

    void addEffectCallBack( EffectShaderCallBack * );

private:
    EffectShader * const effect_;
    EffectShaderCallBack * effectCallBack_;

private:
    RowMajorMatrix44f matProjView_;
    ShaderVariable * matWVP_;

};

