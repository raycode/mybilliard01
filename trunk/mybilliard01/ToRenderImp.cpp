#include "Stdafx.h"
#include "my_app.h"


ToRenderImp::ToRenderImp( Node * node, EffectShader * effect )
: node_( node )
, effect_( effect )
{
    assert( node_ );
    assert( effect_ );

    world_ = effect_->createVariableByName( L"g_mWorld" );
    wvp_ = effect_->createVariableByName( L"g_mWorldViewProjection" );
    assert( world_ );
    assert( wvp_ );
}

void ToRenderImp::updateMatrix( NxActor * actor,
    const RowMajorMatrix44f & matView, const RowMajorMatrix44f & matProjView )
{
    actor->getGlobalPose().getColumnMajor44( columnMajor44_World_ );
    matView.GetColumnMajor( columnMajor44_View_ );

    RowMajorMatrix44f matWorld;
    actor->getGlobalPose().getRowMajor44( matWorld );
    (matProjView * matWorld).GetColumnMajor( columnMajor44_WVP_ );
}

void ToRenderImp::display()
{
    world_->setFloatArray( columnMajor44_World_, 16u );
    wvp_->setFloatArray( columnMajor44_WVP_, 16u );
    effect_->renderWithTechnique( this );
}

void ToRenderImp::displayPass( size_t pass ) {
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect display for each pass" );
    node_->display();
    DXUT_EndPerfEvent();
}

