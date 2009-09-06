#include "StdAfx.h"
#include "my_app.h"


MyEffectShaderFeederImp::MyEffectShaderFeederImp( bool bShared )
: RenderMonkeySemanticFeeder( bShared )
{
}

void MyEffectShaderFeederImp::updateProjection_shadowMap( size_t index, const RowMajorMatrix44f & matProj )
{

}

void MyEffectShaderFeederImp::updateView_shadowMap(
    size_t index,
    const NxVec3 & cameraPos,
    const NxVec3 & cameraDir,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{

}

void MyEffectShaderFeederImp::setEffectShader( EffectShader * effect )
{
    RenderMonkeySemanticFeeder::setEffectShader( effect );
}

void MyEffectShaderFeederImp::updateModelMatrix( const RowMajorMatrix44f & matWorld )
{
    RenderMonkeySemanticFeeder::updateModelMatrix( matWorld );

}


