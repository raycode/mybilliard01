#include "StdAfx.h"
#include "my_app.h"


RenderTargetChainImp::RenderTargetChainImp( RenderBufferFactory * renderFactory, wstring effectFilename,
    size_t width, size_t height, wstring outputWidthInverse, wstring outputHeightInverse,
    wstring inputTextureName, wstring inputWidthInverse, wstring inputHeightInverse )
{
    renderTarget_ = renderFactory->createRenderTarget( width, height );
    assert( renderTarget_ );

    const size_t actualWidth = renderTarget_->getRenderTargetTexture()->getWidth();
    const size_t actualHeight = renderTarget_->getRenderTargetTexture()->getHeight();

    effect_ = renderFactory->createEffectShader( effectFilename );
    assert( effect_ );
    if( NULL == effect_ ) throw exception();

    ShaderVariable * const tex = effect_->createVariableByName( inputTextureName );
    assert( tex );
    if( tex ) tex->setTexture( renderTarget_->getRenderTargetTexture() );

    ShaderVariable * const outputWidthInv = effect_->createVariableByName( outputWidthInverse );
    assert( outputWidthInv );
    if( outputWidthInv ) outputWidthInv->setFloat( 1.f / (float) actualWidth );

    ShaderVariable * const outputHeightInv = effect_->createVariableByName( outputHeightInverse );
    assert( outputHeightInv );
    if( outputHeightInv ) outputHeightInv->setFloat( 1.f / (float) actualHeight );

    inputWidthInv_ = effect_->createVariableByName( inputWidthInverse );
    assert( inputWidthInv_ );
    inputHeightInv_ = effect_->createVariableByName( inputHeightInverse );
    assert( inputHeightInv_ );

    createQuadVertexBuffer( renderFactory );
}

bool RenderTargetChainImp::displayOnRenderTarget( Render * render, RenderTargetCallBack * callBack ) {
    return renderTarget_->displayOnRenderTarget( render, callBack );
}

void RenderTargetChainImp::displayOnRenderTargetCallBack( Render * render ) {
    inputWidthInv_->setFloat( 1.f / (float) render->getRenderTargetWidth() );
    inputHeightInv_->setFloat( 1.f / (float) render->getRenderTargetHeight() );

    render->clear_Z( 1.0f );
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setNone();

    effect_->renderWithTechnique( this );
}

void RenderTargetChainImp::displayPass( size_t pass ) {
    quadVertexBuffer_->drawPrimitive_TRIANGLESTRIP();
}

void RenderTargetChainImp::createQuadVertexBuffer( RenderBufferFactory * renderFactory )
{
    float quadVertices[] = {
        -1.f,  1.f, 0.f,
        1.f,  1.f, 0.f,
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f
    };
    quadVertexBuffer_ = renderFactory->createVertexBuffer_static( 4u, quadVertices );
}

Texture * RenderTargetChainImp::getRenderTargetTexture() {
    return renderTarget_->getRenderTargetTexture();
}

