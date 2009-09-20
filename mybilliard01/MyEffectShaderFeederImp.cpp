#include "StdAfx.h"
#include "my_app.h"


MyEffectShaderFeederImp::MyEffectShaderFeederImp( bool bShared )
: RenderMonkeySemanticFeeder( bShared )
{
}

void MyEffectShaderFeederImp::updateProjection_shadowMap( size_t index, const RowMajorMatrix44f & matProj ) {
    shadowMaps_.at( index ).matProj_ = matProj;

    MY_FOR_EACH( ShadowMapSemantic::ActiveSemantics, iter, shadowMaps_.at( index ).activeSemantics_proj_ )
        uploadShadowMapValue( index, *iter );
}

void MyEffectShaderFeederImp::updateView_shadowMap(
    size_t index,
    const NxVec3 & lightPos,
    const NxVec3 & lightDir,
    const RowMajorMatrix44f & matView,
    const RowMajorMatrix44f & matProjView )
{
    shadowMaps_.at( index ).lightPos_ = lightPos;
    shadowMaps_.at( index ).lightDir_ = lightDir;
    shadowMaps_.at( index ).matView_ = matView;
    shadowMaps_.at( index ).matProjView_ = matProjView;

    MY_FOR_EACH( ShadowMapSemantic::ActiveSemantics, iter, shadowMaps_.at( index ).activeSemantics_view_ )
        uploadShadowMapValue( index, *iter );
}

void MyEffectShaderFeederImp::updateModelMatrix( const RowMajorMatrix44f & matWorld )
{
    RenderMonkeySemanticFeeder::updateModelMatrix( matWorld );

    matWorld_ = matWorld;

    for( size_t index = 0; index < shadowMaps_.size(); ++index )
        MY_FOR_EACH( ShadowMapSemantic::ActiveSemantics, iter, shadowMaps_.at( index ).activeSemantics_world_ )
            uploadShadowMapValue( index, *iter );
}

void MyEffectShaderFeederImp::uploadShadowMapValue( size_t index, int whichSemantic )
{
    ShadowMapSemantic * const shadowMap = &( shadowMaps_[ index ] );

    float floatArray[ 16 ];
    size_t countOfFloat = 16;

    switch( whichSemantic )
    {
    case Position:
        memcpy( (void*) floatArray, (void*) shadowMap->lightPos_.get(), sizeof( float ) * 3 );
        floatArray[ 3 ] = 1.f;
        countOfFloat = 4;
        break;
    case DIrection:
        memcpy( (void*) floatArray, (void*) shadowMap->lightDir_.get(), sizeof( float ) * 3 );
        floatArray[ 3 ] = 0.f;
        countOfFloat = 4;
        break;

    case World:               matWorld_.GetColumnMajor( floatArray ); break;
    case View:                shadowMap->matView_.GetColumnMajor( floatArray ); break;
    case Projection:          shadowMap->matProj_.GetColumnMajor( floatArray ); break;
    case WorldView:           (shadowMap->matView_ * matWorld_).GetColumnMajor( floatArray ); break;
    case ViewProjection:      shadowMap->matProjView_.GetColumnMajor( floatArray ); break;
    case WorldViewProjection: (shadowMap->matProjView_ * matWorld_).GetColumnMajor( floatArray ); break;
    }
    
    shadowMap->shaderVariables_[ whichSemantic ]->setFloatArray( floatArray, countOfFloat );
}

void MyEffectShaderFeederImp::initShadowMapSemantics( EffectShader * effect )
{

#define INIT_SEMANTIC( INDEX, SEMANTIC, WHERETO ) \
    {   wstringstream semanticName; \
        semanticName << L"Light" << setw( 2 ) << setfill< wchar_t >( '0' ) << INDEX << L"_" << L#SEMANTIC; \
        if( getEffectShader()->hasVariableBySemantic( semanticName.str() ) ) \
        {   bFound = true; \
            if( shadowMaps_.size() <= INDEX ) shadowMaps_.resize( INDEX + 1 ); \
            shadowMaps_[ INDEX ].shaderVariables_[ SEMANTIC ] \
                = getEffectShader()->createVariableBySemantic( semanticName.str() ); \
            shadowMaps_[ INDEX ].WHERETO.insert( SEMANTIC ); }}

    for( size_t i = 0; i < 100; ++i )
    {
        bool bFound = false;
        INIT_SEMANTIC( i, Position, activeSemantics_view_ );
        INIT_SEMANTIC( i, DIrection, activeSemantics_view_ );

        INIT_SEMANTIC( i, World, activeSemantics_world_ );
        INIT_SEMANTIC( i, View, activeSemantics_view_ );
        INIT_SEMANTIC( i, Projection, activeSemantics_proj_ );
        INIT_SEMANTIC( i, WorldView, activeSemantics_world_ );
        INIT_SEMANTIC( i, ViewProjection, activeSemantics_view_ );
        INIT_SEMANTIC( i, WorldViewProjection, activeSemantics_world_ );

        if( false == bFound ) break;
    }
#undef INIT_SEMANTIC
}

void MyEffectShaderFeederImp::setEffectShader( EffectShader * effect )
{
    RenderMonkeySemanticFeeder::setEffectShader( effect );

    initShadowMapSemantics( effect );
}



