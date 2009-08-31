#include "stdafx.h"
#include "my_app.h"


void MyRenderEventListenerImp::createShadowMap( RenderBufferFactory * renderFactory ) {
    shadowRenderTarget_ = RenderTargetPtr( renderFactory->createRenderTarget( 256, 256 ), RenderBufferFactory::Destroyer( renderFactory ) );
    shadowFeeder_ = GlobalEffectShaderFeederPtr( new ShadowMapEffectShaderFeeder() );
    assert( NULL != shadowRenderTarget_ );
    assert( NULL != shadowFeeder_ );
}

EffectShaderFeeder * MyRenderEventListenerImp::createEffectFeeder( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstString::effectFilenameByNodeName( nodeName );
    EffectShaderPtr const effect = EffectShaderPtr( renderFactory->createEffectShader( effectFilename ), RenderBufferFactory::Destroyer( renderFactory ) );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    EffectShaderFeederPtr newFeeder = EffectShaderFeederPtr( new RenderMonkeySemanticFeeder( node, effect, shadowRenderTarget_->getTexture() ) );
    feeders_.push_back( newFeeder );

    findSharedVariables( effect.get() );
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

