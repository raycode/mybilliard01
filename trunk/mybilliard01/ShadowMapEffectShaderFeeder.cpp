#include "StdAfx.h"
#include "my_app.h"


ShadowMapEffectShaderFeeder::ShadowMapEffectShaderFeeder( EffectShader * effect )
: effect_( effect )
, matWVP_( effect->createVariableByName( L"Light0_WorldLightProjection" ) )
{
}

void ShadowMapEffectShaderFeeder::display( NxActor * actor )
{
    RowMajorMatrix44f matWorld;
    actor->getGlobalPose().getRowMajor44( matWorld );

    float matWVP[ 16 ];
    (matProjView_ * matWorld).GetColumnMajor( matWVP );

    matWVP_->setFloatArray( matWVP, 16u );

    effect_->renderWithTechnique( effectCallBack_ );
}

void ShadowMapEffectShaderFeeder::updateProjection( const RowMajorMatrix44f & matProj ) {
}

void ShadowMapEffectShaderFeeder::updateMatrix(
                          const NxVec3 & lightPos,
                          const NxVec3 & lightDir,
                          const RowMajorMatrix44f & matView,
                          const RowMajorMatrix44f & matProjView )
{
    matProjView_ = matProjView;
}

void ShadowMapEffectShaderFeeder::addEffectCallBack( EffectShaderCallBack * callBack ) {
    effectCallBack_ = callBack;
}

