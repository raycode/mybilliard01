#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShader * RenderBufferFactoryDX9Imp::createEffectShader( wstring filename )
{
    EffectShaderDX9Ptr newEffect = findEffectShaderFromAlreadyCreated( filename );
    if( NULL == newEffect ) newEffect = EffectShaderDX9Ptr( new EffectShaderDX9Imp( getD3D9Device(), filename, d3dEffectPool_.get(), this ), ReleasableResourceDX9::Destroyer() );
    if( NULL == newEffect ) return NULL;

    const bool bAcquire = newEffect->acquireResource();
    RETURN_VALUE_UNLESS( bAcquire, NULL );

    pushBackToActiveQueue( E_EFFECT_SHADERS, newEffect );
    return newEffect.get();
}

EffectShaderDX9Ptr RenderBufferFactoryDX9Imp::findEffectShaderFromAlreadyCreated( wstring filename ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i )
    {
        MY_FOR_EACH( ReleasableResources, iter, resources_[ E_EFFECT_SHADERS ][ i ] )
        {
            EffectShaderDX9ImpPtr oldEffectShader = dynamic_pointer_cast< EffectShaderDX9Imp >( *iter );
            if( oldEffectShader->getFilename() != filename ) continue;

            return oldEffectShader;
        }
    }
    return EffectShaderDX9Ptr();
}

Texture * RenderBufferFactoryDX9Imp::createTexture( wstring filename )
{
    if( filename.empty() ) return NULL;

    TextureDX9Ptr newTexture = findTextureFromAlreadyCreated( filename );
    if( NULL == newTexture ) newTexture = TextureDX9Ptr( new TextureDX9Imp( getD3D9Device(), filename ), ReleasableResourceDX9::Destroyer() );
    if( NULL == newTexture ) return NULL;

    const bool bAcquire = newTexture->acquireResource();
    assert( bAcquire );
    if( false == bAcquire ) return NULL;

    pushBackToActiveQueue( E_TEXTURES, newTexture );
    return newTexture.get();
}

TextureDX9Ptr RenderBufferFactoryDX9Imp::findTextureFromAlreadyCreated( wstring filename )
{
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i )
    {
        MY_FOR_EACH( ReleasableResources, iter, resources_[ E_TEXTURES ][ i ] )
        {
            TextureDX9Ptr oldTexture = dynamic_pointer_cast< TextureDX9 >( *iter );
            if( false == oldTexture->isFromFile() ) continue;
            if( oldTexture->getFilename() != filename ) continue;

            return oldTexture;
        }
    }
    return TextureDX9Ptr();
}

RenderTarget * RenderBufferFactoryDX9Imp::createRenderTarget( size_t width, size_t height )
{
    // I'm not sure how to allow users to specify format here.
    RenderTargetDX9Ptr newRenderTarget = RenderTargetDX9Ptr( new RenderTargetDX9Imp( getD3D9Device(), width, height ), ReleasableResourceDX9::Destroyer() );
    if( NULL == newRenderTarget ) return NULL;

    const bool bAcquire = newRenderTarget->acquireResource();
    assert( bAcquire );
    if( false == bAcquire ) return NULL;

    pushBackToActiveQueue( E_RENDER_TARGETS, newRenderTarget );
    return newRenderTarget.get();
}


}
