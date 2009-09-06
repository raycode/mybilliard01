#include "stdafx.h"
#include "my_app.h"


RenderMonkeySemanticFeeder::RenderMonkeySemanticFeeder( bool bShared )
: bShared_( bShared )
{
}

void RenderMonkeySemanticFeeder::setEffectShader( EffectShader * effect ) {
    effect_ = effect;

    initPredefinedSemantics();

    if( false == bShared_ ) initRenderTargets();
}

EffectShader * RenderMonkeySemanticFeeder::getEffectShader() {
    return effect_;
}

void RenderMonkeySemanticFeeder::updateProjection_camera( const RowMajorMatrix44f & matProj ) {
    matProj_ = matProj;

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Projection_ )
    {
        updateForPredefinedSemantic( *iter );
        uploadValue( *iter );
    }
}

void RenderMonkeySemanticFeeder::updateView_camera(
    const NxVec3 & cameraPos,
    const NxVec3 & cameraDir,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{
    cameraPos_ = cameraPos;
    cameraDir_ = cameraDir;
    matView_ = matView;
    matProjView_ = matProjView;

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Camera_ )
    {
        updateForPredefinedSemantic( *iter );
        uploadValue( *iter );
    }
}

void RenderMonkeySemanticFeeder::updateModelMatrix( const RowMajorMatrix44f & matWorld )
{
    matWorld_ = matWorld;

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Model_ )
    {
        updateForPredefinedSemantic( *iter );
        uploadValue( *iter );
    }
}

bool RenderMonkeySemanticFeeder::displayWithEffect( EffectShaderCallBack * callBack )
{
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect with technique" );
    const bool bRst = effect_->renderWithTechnique( callBack );
    DXUT_EndPerfEvent();

    return bRst;
}

void RenderMonkeySemanticFeeder::initRenderTargets() {
    // todo
}

bool RenderMonkeySemanticFeeder::initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, ActiveSemanticFlags & whereToStore, size_t countOfFloat )
{
    if( false == effect_->hasVariableBySemantic( nameOfSemantic ) ) return false;

    EffectShaderVariable * const variableForSemantic = effect_->createEffectVariableBySemantic( nameOfSemantic );
    if( bShared_ != variableForSemantic->isShared() ) return false;

    predefinedVariables_[ whichSemantic ] = variableForSemantic;
    whereToStore.insert( whichSemantic );

    temporaryStorage_[ whichSemantic ].resize( countOfFloat );

    return true;
}

void RenderMonkeySemanticFeeder::initPredefinedSemantics() {

#define INIT_SEMANTIC( SEMANTIC, WHERE_TO_STORE, COUNT_OF_FLOAT ) initPredefinedSemanticForEach( SEMANTIC, L#SEMANTIC, WHERE_TO_STORE, COUNT_OF_FLOAT );

    INIT_SEMANTIC( ViewPosition, activeSemantics_Camera_, 4 );
    INIT_SEMANTIC( ViewDirection, activeSemantics_Camera_, 4 );

    INIT_SEMANTIC( World, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldTranspose, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldInverse, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldInverseTranspose, activeSemantics_Model_, 16 );

    INIT_SEMANTIC( View, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewTranspose, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewInverse, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewInverseTranspose, activeSemantics_Camera_, 16 );

    INIT_SEMANTIC( Projection, activeSemantics_Projection_, 16 );
    INIT_SEMANTIC( ProjectionTranspose, activeSemantics_Projection_, 16 );
    INIT_SEMANTIC( ProjectionInverse, activeSemantics_Projection_, 16 );
    INIT_SEMANTIC( ProjectionInverseTranspose, activeSemantics_Projection_, 16 );

    INIT_SEMANTIC( WorldView, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewTranspose, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewInverse, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewInverseTranspose, activeSemantics_Model_, 16 );

    INIT_SEMANTIC( ViewProjection, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewProjectionTranspose, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewProjectionInverse, activeSemantics_Camera_, 16 );
    INIT_SEMANTIC( ViewProjectionInverseTranspose, activeSemantics_Camera_, 16 );

    INIT_SEMANTIC( WorldViewProjection, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewProjectionTranspose, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewProjectionInverse, activeSemantics_Model_, 16 );
    INIT_SEMANTIC( WorldViewProjectionInverseTranspose, activeSemantics_Model_, 16 );
}


void RenderMonkeySemanticFeeder::updateForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = &( temporaryStorage_[ whichSemantic ][ 0 ] );

    switch( whichSemantic )
    {
    case ViewPosition:  memcpy( (void*)colMajor44f, (void*)cameraPos_.get(), sizeof(float) *3 ); colMajor44f[3] = 1.f; break;
    case ViewDirection: memcpy( (void*)colMajor44f, (void*)cameraDir_.get(), sizeof(float) *3 ); colMajor44f[3] = 0.f; break;

    case World:                 matWorld_.GetColumnMajor( colMajor44f ); break;
    case WorldTranspose:        matWorld_.Transpose().GetColumnMajor( colMajor44f ); break;
    case WorldInverse:          matWorld_.Inverse().GetColumnMajor( colMajor44f ); break;
    case WorldInverseTranspose: matWorld_.Inverse().Transpose().GetColumnMajor( colMajor44f ); break;

    case View:                 matView_.GetColumnMajor( colMajor44f ); break;
    case ViewTranspose:        matView_.Transpose().GetColumnMajor( colMajor44f ); break;
    case ViewInverse:          matView_.Inverse().GetColumnMajor( colMajor44f ); break;
    case ViewInverseTranspose: matView_.Inverse().Transpose().GetColumnMajor( colMajor44f ); break;

    case Projection:                 matProj_.GetColumnMajor( colMajor44f ); break;
    case ProjectionTranspose:        matProj_.Transpose().GetColumnMajor( colMajor44f ); break;
    case ProjectionInverse:          matProj_.Inverse().GetColumnMajor( colMajor44f ); break;
    case ProjectionInverseTranspose: matProj_.Inverse().Transpose().GetColumnMajor( colMajor44f ); break;

    case WorldView:                 (matView_ * matWorld_).GetColumnMajor( colMajor44f ); break;
    case WorldViewTranspose:        (matView_ * matWorld_).Transpose().GetColumnMajor( colMajor44f ); break;
    case WorldViewInverse:          (matView_ * matWorld_).Inverse().GetColumnMajor( colMajor44f ); break;
    case WorldViewInverseTranspose: (matView_ * matWorld_).Inverse().Transpose().GetColumnMajor( colMajor44f ); break;

    case ViewProjection:                 matProjView_.GetColumnMajor( colMajor44f ); break;
    case ViewProjectionTranspose:        matProjView_.Transpose().GetColumnMajor( colMajor44f ); break;
    case ViewProjectionInverse:          matProjView_.Inverse().GetColumnMajor( colMajor44f ); break;
    case ViewProjectionInverseTranspose: matProjView_.Inverse().Transpose().GetColumnMajor( colMajor44f ); break;

    case WorldViewProjection:                 (matProjView_ * matWorld_).GetColumnMajor( colMajor44f ); break;
    case WorldViewProjectionTranspose:        (matProjView_ * matWorld_).Transpose().GetColumnMajor( colMajor44f ); break;
    case WorldViewProjectionInverse:          (matProjView_ * matWorld_).Inverse().GetColumnMajor( colMajor44f ); break;
    case WorldViewProjectionInverseTranspose: (matProjView_ * matWorld_).Inverse().Transpose().GetColumnMajor( colMajor44f ); break;
    }
}


void RenderMonkeySemanticFeeder::uploadValue( int whichSemantic ) {
    const size_t countOfFloat = temporaryStorage_[ whichSemantic ].size();
    const float * const floatArray = &( temporaryStorage_[ whichSemantic ][ 0 ]);
    predefinedVariables_[ whichSemantic ]->setFloatArray( floatArray, countOfFloat );
}


