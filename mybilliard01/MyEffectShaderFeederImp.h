#pragma once


class MyEffectShaderFeederImp
    : public RenderMonkeySemanticFeeder
    , IMPLEMENTS_INTERFACE( MyEffectShaderFeeder )
{
public: // EffectShaderShadowMapFeeder
    virtual void updateProjection_shadowMap( size_t index, const RowMajorMatrix44f & matProj ) OVERRIDE;

    virtual void updateView_shadowMap(
        size_t index,
        const NxVec3 & cameraPos,
        const NxVec3 & cameraDir,
        const RowMajorMatrix44f & matView,
        const RowMajorMatrix44f & matProjView ) OVERRIDE;

public: // from EffectShaderFeeder
    virtual void setEffectShader( EffectShader * ) OVERRIDE;
    virtual void updateModelMatrix( const RowMajorMatrix44f & matWorld ) OVERRIDE;

public:
    MyEffectShaderFeederImp( bool bShared );

};

