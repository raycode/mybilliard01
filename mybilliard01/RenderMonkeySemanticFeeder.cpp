#include "stdafx.h"
#include "my_app.h"


RenderMonkeySemanticFeeder::RenderMonkeySemanticFeeder( Node * node, EffectShaderPtr effect )
: node_( node )
, effect_( effect )
{
    assert( node_ );
    assert( effect_ );
    initPredefinedSemantics();
}

const wstring RenderMonkeySemanticFeeder::effectFilename = L"..\\asset\\shaders\\textured pong.fx";

void RenderMonkeySemanticFeeder::updateMatrix(
    NxActor * actor,
    const NxVec3 & cameraPos,
    const NxVec3 & cameraDir,
    const RowMajorMatrix44f & matProj,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{
    actor->getGlobalPose().getRowMajor44( matWorld_ );

    cameraPos_ = cameraPos;
    cameraDir_ = cameraDir;
    matProj_ = matProj;
    matView_ = matView;
    matProjView_ = matProjView;

    MY_FOR_EACH( ActivePredefinedSemantics_Matrix, iter, activePredefinedSemantics_Matrix_ )
        updateMatrixForPredefinedSemantic( *iter );

    MY_FOR_EACH( ActivePredefinedSemantics_Vec4, iter, activePredefinedSemantics_Vec4_ )
        updateMatrixForPredefinedSemantic( *iter );
}

void RenderMonkeySemanticFeeder::display()
{
    //OutputDebugStr( wstring( L"Node name: " + node_->getName() + L"\n" ).c_str() );

    MY_FOR_EACH( ActivePredefinedSemantics_Matrix, iter, activePredefinedSemantics_Matrix_ )
        setMatrixForPredefinedSemantic( *iter );

    MY_FOR_EACH( ActivePredefinedSemantics_Vec4, iter, activePredefinedSemantics_Vec4_ )
        setVec4ForPredefinedSemantic( *iter );

    effect_->renderWithTechnique( this );
}

void RenderMonkeySemanticFeeder::displayPass( size_t pass )
{
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect display for each pass" );
    node_->display();
    DXUT_EndPerfEvent();
}

void RenderMonkeySemanticFeeder::initPredefinedSemantics() {

#define INIT_VEC3_SEMANTIC( SEMANTIC ) if( effect_->hasVariableBySemantic( L#SEMANTIC ) ) { predef_[ SEMANTIC ] = effect_->createVariableBySemantic( L#SEMANTIC ); activePredefinedSemantics_Vec4_.push_back( SEMANTIC ); }

    INIT_VEC3_SEMANTIC( ViewPosition );
    INIT_VEC3_SEMANTIC( ViewDirection );

#define INIT_MATRIX_SEMANTIC( SEMANTIC ) if( effect_->hasVariableBySemantic( L#SEMANTIC ) ) { predef_[ SEMANTIC ] = effect_->createVariableBySemantic( L#SEMANTIC ); activePredefinedSemantics_Matrix_.push_back( SEMANTIC ); }

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


void RenderMonkeySemanticFeeder::updateMatrixForPredefinedSemantic( int whichSemantic )
{
    float * const colMajor44f = predefinedSemantics_Matrix44f_[ whichSemantic ];

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

void RenderMonkeySemanticFeeder::setMatrixForPredefinedSemantic( int whichSemantic ) {
    predef_[ whichSemantic ]->setFloatArray( predefinedSemantics_Matrix44f_[ whichSemantic ], 16u );

    //const float * ptr = predefinedSemantics_Matrix44f_[ whichSemantic ];
    //wchar_t tmp[256];
    //_snwprintf_s( tmp, 256, L"%d: %f %f %f %f [1] %f %f %f %f [2] %f %f %f %f [3] %f %f %f %f\n", whichSemantic, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7], ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15] );
    //OutputDebugStr( tmp );
}

void RenderMonkeySemanticFeeder::setVec4ForPredefinedSemantic( int whichSemantic ) {
    predef_[ whichSemantic ]->setFloatArray( predefinedSemantics_Matrix44f_[ whichSemantic ], 4u );
}


