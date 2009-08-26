#include "stdafx.h"
#include "my_app.h"


EffectShaderFeeder * MyRenderEventListenerImp::createToRender( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstEffectFilename::getEffectFilenameByNodeName( nodeName );
    EffectShaderPtr const effect = EffectShaderPtr( renderFactory->createEffectShader( effectFilename ), RenderBufferFactory::Releaser( renderFactory ) );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    EffectShaderFeederPtr newFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( node, effect, renderFactory ) );
    feeders_.push_back( newFeeder );

    findSharedVariables( effect.get() );
    return newFeeder.get();
}

void MyRenderEventListenerImp::findSharedVariables( EffectShader * effect ) {

    const size_t nVariables = effect->getNumberOfVariables();

    for( size_t i = 0; i < nVariables; ++i )
    {
        EffectShaderVariablePtr const sharedVariable = ShaderVariablePtr( effect->createEffectVariableByIndex( i ), Shader::Releaser( effect ) );
        if( false == sharedVariable->isShared() ) continue;

        const wstring variableName = sharedVariable->getVariableName();
        if( sharedVariables_.find( variableName ) != sharedVariables_.end() ) continue;

        sharedVariables_.insert( SharedVariables::value_type( variableName, sharedVariable ) );
    }
}

ShaderVariable * MyRenderEventListenerImp::getSharedVariable( wstring name ) {
    SharedVariables::const_iterator iter = sharedVariables_.find( name );
    if( sharedVariables_.end() == iter ) return NULL;
    return iter->second.get();
}

