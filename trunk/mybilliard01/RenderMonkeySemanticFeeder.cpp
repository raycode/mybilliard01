#include "stdafx.h"
#include "my_app.h"
using namespace RenderMonkeySemantics;


RenderMonkeySemanticFeeder::RenderMonkeySemanticFeeder( bool bShared )
: bShared_( bShared )
{
}

void RenderMonkeySemanticFeeder::setEffectShader( EffectShader * effect ) {
    effect_ = effect;

    collectPredefinedSemantics();

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

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Matrix_ )
        updateMatrixForPredefinedSemantic( *iter );

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Vec4_ )
        updateVec4ForPredefinedSemantic( *iter );
}

void RenderMonkeySemanticFeeder::updateModelMatrix( const RowMajorMatrix44f & matWorld )
{
    matWorld_ = matWorld;
}

bool RenderMonkeySemanticFeeder::displayWithEffect( EffectShaderCallBack * callBack )
{
    //OutputDebugStr( wstring( L"Node name: " + node_->getName() + L"\n" ).c_str() );

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Matrix_ )
        uploadValue( *iter, 16u );

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Vec4_ )
        uploadValue( *iter, 4u );

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect with technique" );
    const bool bRst = effect_->renderWithTechnique( callBack );
    DXUT_EndPerfEvent();

    return bRst;
}

void RenderMonkeySemanticFeeder::initRenderTargets() {
    // todo
}

bool RenderMonkeySemanticFeeder::initPredefinedSemanticForEach( int whichSemantic, wstring nameOfSemantic, ActiveSemanticFlags & whereToStore )
{
    if( false == effect_->hasVariableBySemantic( nameOfSemantic ) ) return false;

    EffectShaderVariable * const variableForSemantic = effect_->createEffectVariableBySemantic( nameOfSemantic );
    if( bShared_ != variableForSemantic->isShared() ) return false;

    predefinedVariables_[ whichSemantic ] = variableForSemantic;
    whereToStore.push_back( whichSemantic );
    return true;
}

void RenderMonkeySemanticFeeder::collectPredefinedSemantics() {

#define INIT_VEC3_SEMANTIC( SEMANTIC ) initPredefinedSemanticForEach( SEMANTIC, L#SEMANTIC, activeSemantics_Vec4_ );

    INIT_VEC3_SEMANTIC( ViewPosition );
    INIT_VEC3_SEMANTIC( ViewDirection );

#define INIT_MATRIX_SEMANTIC( SEMANTIC ) initPredefinedSemanticForEach( SEMANTIC, L#SEMANTIC, activeSemantics_Matrix_ );

    INIT_MATRIX_SEMANTIC( World );
    INIT_MATRIX_SEMANTIC( WorldTranspose );
    INIT_MATRIX_SEMANTIC( WorldInverse );
    INIT_MATRIX_SEMANTIC( WorldInverseTranspose );

    INIT_MATRIX_SEMANTIC( View );
    INIT_MATRIX_SEMANTIC( ViewTranspose );
    INIT_MATRIX_SEMANTIC( ViewInverse );
    INIT_MATRIX_SEMANTIC( ViewInverseTranspose );

    INIT_MATRIX_SEMANTIC( Projection );
    INIT_MATRIX_SEMANTIC( ProjectionTranspose );
    INIT_MATRIX_SEMANTIC( ProjectionInverse );
    INIT_MATRIX_SEMANTIC( ProjectionInverseTranspose );

    INIT_MATRIX_SEMANTIC( WorldView );
    INIT_MATRIX_SEMANTIC( WorldViewTranspose );
    INIT_MATRIX_SEMANTIC( WorldViewInverse );
    INIT_MATRIX_SEMANTIC( WorldViewInverseTranspose );

    INIT_MATRIX_SEMANTIC( ViewProjection );
    INIT_MATRIX_SEMANTIC( ViewProjectionTranspose );
    INIT_MATRIX_SEMANTIC( ViewProjectionInverse );
    INIT_MATRIX_SEMANTIC( ViewProjectionInverseTranspose );

    INIT_MATRIX_SEMANTIC( WorldViewProjection );
    INIT_MATRIX_SEMANTIC( WorldViewProjectionTranspose );
    INIT_MATRIX_SEMANTIC( WorldViewProjectionInverse );
    INIT_MATRIX_SEMANTIC( WorldViewProjectionInverseTranspose );
}


void RenderMonkeySemanticFeeder::updateVec4ForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = temporaryStorage16f[ whichSemantic ];

    switch( whichSemantic )
    {
    case ViewPosition:  memcpy( (char*)colMajor44f, (char*)cameraPos_.get(), sizeof(NxVec3) ); colMajor44f[3] = 1.f; break;
    case ViewDirection: memcpy( (char*)colMajor44f, (char*)cameraDir_.get(), sizeof(NxVec3) ); colMajor44f[3] = 0.f; break;

    }
}

void RenderMonkeySemanticFeeder::updateMatrixForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = temporaryStorage16f[ whichSemantic ];

    switch( whichSemantic )
    {
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


void RenderMonkeySemanticFeeder::uploadValue( int whichSemantic, size_t count ) {
    predefinedVariables_[ whichSemantic ]->setFloatArray( temporaryStorage16f[ whichSemantic ], count );

    //const float * ptr = temporaryStorage16f[ whichSemantic ];
    //wchar_t tmp[256];
    //_snwprintf_s( tmp, 256, L"%d: %f %f %f %f [1] %f %f %f %f [2] %f %f %f %f [3] %f %f %f %f\n", whichSemantic, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15] );
    //OutputDebugStr( tmp );
}


