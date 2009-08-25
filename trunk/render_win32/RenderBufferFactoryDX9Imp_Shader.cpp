#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShader * RenderBufferFactoryDX9Imp::createEffectShader( wstring filename )
{
    EffectShaderDX9Ptr newEffect = copyEffectShaderFromAlreadyCreated( filename );
    if( NULL == newEffect ) newEffect = EffectShaderDX9Ptr( new EffectShaderDX9Imp( getD3D9Device(), filename, &*d3dEffectPool_, this ), ReleasableResourceDX9::Releaser() );
    if( NULL == newEffect ) return NULL;

    const bool bAcquired = newEffect->acquireResource();
    assert( bAcquired );
    if( false == bAcquired ) return NULL;

    pushBackToActiveQueue( E_EFFECT_SHADERS, newEffect );
    return &*newEffect;
}

EffectShaderDX9Ptr RenderBufferFactoryDX9Imp::copyEffectShaderFromAlreadyCreated( wstring filename ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i )
    {
        MY_FOR_EACH( ReleasableResources, iter, resources_[ E_EFFECT_SHADERS ][ i ] )
        {
            EffectShaderDX9Imp * const effectShader = dynamic_cast< EffectShaderDX9Imp * >( &**iter );
            if( effectShader->getFilename() != filename ) continue;

            return EffectShaderDX9Ptr( new EffectShaderDX9Imp( *effectShader ), ReleasableResourceDX9::Releaser() );
        }
    }
    return EffectShaderDX9Ptr();
}

Texture * RenderBufferFactoryDX9Imp::createTexture( wstring filename )
{
    if( filename.empty() ) return NULL;

    TextureDX9Ptr newTexture = TextureDX9Ptr( new TextureDX9Imp( getD3D9Device(), filename ), ReleasableResourceDX9::Releaser() );
    if( NULL == newTexture ) return NULL;

    const bool bAcquired = newTexture->acquireResource();
    assert( bAcquired );
    if( false == bAcquired ) return NULL;

    pushBackToActiveQueue( E_TEXTURE, newTexture );
    return newTexture.get();
}


}
