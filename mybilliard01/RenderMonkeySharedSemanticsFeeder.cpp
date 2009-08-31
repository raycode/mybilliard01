#include "stdafx.h"
#include "my_app.h"
using namespace RenderMonkeySemantics;


void RenderMonkeySharedSemanticsFeeder::updateProjection( const RowMajorMatrix44f & matProj ) {
    matProj_ = matProj;
}

void RenderMonkeySharedSemanticsFeeder::updateMatrix(
    const NxVec3 & cameraPos,
    const NxVec3 & cameraDir,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{
    cameraPos_ = cameraPos;
    cameraDir_ = cameraDir;
    matView_ = matView;
    matProjView_ = matProjView;

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Matrix_ ) {
        updateMatrixForPredefinedSemantic( *iter );
        upload( *iter, 16u );
    }

    MY_FOR_EACH( ActiveSemanticFlags, iter, activeSemantics_Vec4_ ) {
        updateVec4ForPredefinedSemantic( *iter );
        upload( *iter, 4u );
    }
}

void RenderMonkeySharedSemanticsFeeder::setSharedVariable( int whichSemantic, ShaderVariable * var, ActiveSemanticFlags &whereToStore )
{
    predefinedVariables_[ whichSemantic ] = var;
    whereToStore.push_back( whichSemantic );
}

void RenderMonkeySharedSemanticsFeeder::appendSharedVariable( ShaderVariable * var ) {
    assert( dynamic_cast< EffectShaderVariable * >( var )->isShared() );

#define APPEND_VEC3_SEMANTIC( SEMANTIC, VAR ) if( VAR->getSemanticName() == L#SEMANTIC ) setSharedVariable( SEMANTIC, VAR, activeSemantics_Vec4_ );

    APPEND_VEC3_SEMANTIC( ViewPosition, var );
    APPEND_VEC3_SEMANTIC( ViewDirection, var );

#define APPEND_MATRIX_SEMANTIC( SEMANTIC, VAR ) if( VAR->getSemanticName() == L#SEMANTIC ) setSharedVariable( SEMANTIC, VAR, activeSemantics_Matrix_ );

    APPEND_MATRIX_SEMANTIC( World, var );
    APPEND_MATRIX_SEMANTIC( WorldTranspose, var );
    APPEND_MATRIX_SEMANTIC( WorldInverse, var );
    APPEND_MATRIX_SEMANTIC( WorldInverseTranspose, var );

    APPEND_MATRIX_SEMANTIC( View, var );
    APPEND_MATRIX_SEMANTIC( ViewTranspose, var );
    APPEND_MATRIX_SEMANTIC( ViewInverse, var );
    APPEND_MATRIX_SEMANTIC( ViewInverseTranspose, var );

    APPEND_MATRIX_SEMANTIC( Projection, var );
    APPEND_MATRIX_SEMANTIC( ProjectionTranspose, var );
    APPEND_MATRIX_SEMANTIC( ProjectionInverse, var );
    APPEND_MATRIX_SEMANTIC( ProjectionInverseTranspose, var );

    APPEND_MATRIX_SEMANTIC( WorldView, var );
    APPEND_MATRIX_SEMANTIC( WorldViewTranspose, var );
    APPEND_MATRIX_SEMANTIC( WorldViewInverse, var );
    APPEND_MATRIX_SEMANTIC( WorldViewInverseTranspose, var );

    APPEND_MATRIX_SEMANTIC( ViewProjection, var );
    APPEND_MATRIX_SEMANTIC( ViewProjectionTranspose, var );
    APPEND_MATRIX_SEMANTIC( ViewProjectionInverse, var );
    APPEND_MATRIX_SEMANTIC( ViewProjectionInverseTranspose, var );

    APPEND_MATRIX_SEMANTIC( WorldViewProjection, var );
    APPEND_MATRIX_SEMANTIC( WorldViewProjectionTranspose, var );
    APPEND_MATRIX_SEMANTIC( WorldViewProjectionInverse, var );
    APPEND_MATRIX_SEMANTIC( WorldViewProjectionInverseTranspose, var );
}


void RenderMonkeySharedSemanticsFeeder::updateVec4ForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = predefinedSemantics_Matrix44f_[ whichSemantic ];

    switch( whichSemantic )
    {
    case ViewPosition:  memcpy( (char*)colMajor44f, (char*)cameraPos_.get(), sizeof(NxVec3) ); colMajor44f[3] = 1.f; break;
    case ViewDirection: memcpy( (char*)colMajor44f, (char*)cameraDir_.get(), sizeof(NxVec3) ); colMajor44f[3] = 0.f; break;

    }
}

void RenderMonkeySharedSemanticsFeeder::updateMatrixForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = predefinedSemantics_Matrix44f_[ whichSemantic ];

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

void RenderMonkeySharedSemanticsFeeder::upload( int whichSemantic, size_t count ) {
    predefinedVariables_[ whichSemantic ]->setFloatArray( predefinedSemantics_Matrix44f_[ whichSemantic ], count );

}

