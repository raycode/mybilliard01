#include "stdafx.h"
#include "my_app.h"
using namespace RenderMonkeySemantics;


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

void RenderMonkeySemanticFeeder::updateCameraProjection( const RowMajorMatrix44f & matProj ) {
    matProj_ = matProj;
}

void RenderMonkeySemanticFeeder::updateCameraMatrix(
    const NxVec3 & cameraPos,
    const NxVec3 & cameraDir,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{
    cameraPos_ = cameraPos;
    cameraDir_ = cameraDir;
    matView_ = matView;
    matProjView_ = matProjView;
}

void RenderMonkeySemanticFeeder::updateModelMatrix( const RowMajorMatrix44f & matWorld )
{
    matWorld_ = matWorld;
}

bool RenderMonkeySemanticFeeder::displayWithEffect( EffectShaderCallBack * callBack )
{
    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_ )
    {
        updateForPredefinedSemantic( *iter );
        uploadValue( *iter );
    }

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect with technique" );
    const bool bRst = effect_->renderWithTechnique( callBack );
    DXUT_EndPerfEvent();

    return bRst;
}

void RenderMonkeySemanticFeeder::initRenderTargets() {
    // todo
}

bool RenderMonkeySemanticFeeder::initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, size_t countOfFloat )
{
    if( false == effect_->hasVariableBySemantic( nameOfSemantic ) ) return false;

    EffectShaderVariable * const variableForSemantic = effect_->createEffectVariableBySemantic( nameOfSemantic );
    if( bShared_ != variableForSemantic->isShared() ) return false;

    predefinedVariables_[ whichSemantic ] = variableForSemantic;
    activeSemantics_.push_back( whichSemantic );

    temporaryStorage_[ whichSemantic ].resize( countOfFloat );

    return true;
}

void RenderMonkeySemanticFeeder::initPredefinedSemantics() {

#define INIT_SEMANTIC( SEMANTIC, COUNT_OF_FLOAT ) initPredefinedSemanticForEach( SEMANTIC, L#SEMANTIC, COUNT_OF_FLOAT );

    INIT_SEMANTIC( ViewPosition, 4 );
    INIT_SEMANTIC( ViewDirection, 3 );

    INIT_SEMANTIC( World, 16 );
    INIT_SEMANTIC( WorldTranspose, 16 );
    INIT_SEMANTIC( WorldInverse, 16 );
    INIT_SEMANTIC( WorldInverseTranspose, 16 );

    INIT_SEMANTIC( View, 16 );
    INIT_SEMANTIC( ViewTranspose, 16 );
    INIT_SEMANTIC( ViewInverse, 16 );
    INIT_SEMANTIC( ViewInverseTranspose, 16 );

    INIT_SEMANTIC( Projection, 16 );
    INIT_SEMANTIC( ProjectionTranspose, 16 );
    INIT_SEMANTIC( ProjectionInverse, 16 );
    INIT_SEMANTIC( ProjectionInverseTranspose, 16 );

    INIT_SEMANTIC( WorldView, 16 );
    INIT_SEMANTIC( WorldViewTranspose, 16 );
    INIT_SEMANTIC( WorldViewInverse, 16 );
    INIT_SEMANTIC( WorldViewInverseTranspose, 16 );

    INIT_SEMANTIC( ViewProjection, 16 );
    INIT_SEMANTIC( ViewProjectionTranspose, 16 );
    INIT_SEMANTIC( ViewProjectionInverse, 16 );
    INIT_SEMANTIC( ViewProjectionInverseTranspose, 16 );

    INIT_SEMANTIC( WorldViewProjection, 16 );
    INIT_SEMANTIC( WorldViewProjectionTranspose, 16 );
    INIT_SEMANTIC( WorldViewProjectionInverse, 16 );
    INIT_SEMANTIC( WorldViewProjectionInverseTranspose, 16 );
}


void RenderMonkeySemanticFeeder::updateForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = &( temporaryStorage_[ whichSemantic ][ 0 ] );

    switch( whichSemantic )
    {
    case ViewPosition:  memcpy( (char*)colMajor44f, (char*)cameraPos_.get(), sizeof(NxVec3) ); colMajor44f[3] = 1.f; break;
    case ViewDirection: memcpy( (char*)colMajor44f, (char*)cameraDir_.get(), sizeof(NxVec3) ); colMajor44f[3] = 0.f; break;

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
    predefinedVariables_[ whichSemantic ]->setFloatArray( &( temporaryStorage_[ whichSemantic ][ 0 ]), countOfFloat );
}


