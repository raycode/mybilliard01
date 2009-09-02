#include "stdafx.h"
#include "my_app.h"


EffectShaderFeeder * MyRenderEventListenerImp::createEffectFeeder( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstString::effectFilenameByNodeName( nodeName );
    EffectShader * const effect = renderFactory->createEffectShader( effectFilename );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    EffectShaderFeederPtr newFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( node, effect ) );

    for( size_t i = 0; i < SIZE_OF_LIGHT_ENUM; ++i ) {
        wstringstream shadowTexName;
        shadowTexName << L"shadow" << i << L"_Tex";
        if( effect->hasVariableByName( shadowTexName.str() ) )
            effect->createVariableByName( shadowTexName.str() )->setTexture( shadowMaps_[ i ]->getRenderTarget() );
    }

    findSharedVariables( effect );

    feeders_.push_back( newFeeder );

    return newFeeder.get();
}

void MyRenderEventListenerImp::findSharedVariables( EffectShader * effect ) {

    const size_t nVariables = effect->getNumberOfVariables();

    for( size_t i = 0; i < nVariables; ++i )
    {
        EffectShaderVariablePtr sharedVariable = EffectShaderVariablePtr( effect->createEffectVariableByIndex( i ), EffectShader::Destroyer( effect ) );
        if( false == sharedVariable->isShared() ) continue;

        const wstring variableName = sharedVariable->getVariableName();
        if( sharedVariables_.find( variableName ) != sharedVariables_.end() ) continue;

        sharedVariables_.insert( SharedVariables::value_type( variableName, sharedVariable ) );
    }
}

ShaderVariable * MyRenderEventListenerImp::getSharedVariable( wstring name ) {
    SharedVariables::const_iterator iter = sharedVariables_.find( name );
    if( sharedVariables_.end() == iter ) return & nullShaderVariable_;
    return iter->second.get();
}

void MyRenderEventListenerImp::createSharedVariableFeeder() 
{
    RenderMonkeySharedSemanticsFeeder * const sharedVaribleFeeder = new RenderMonkeySharedSemanticsFeeder();
    sharedVaribleFeeder_ = GlobalEffectShaderFeederPtr( sharedVaribleFeeder );

    MY_FOR_EACH( SharedVariables, iter, sharedVariables_ )
        sharedVaribleFeeder->appendSharedVariable( iter->second.get() );
}

