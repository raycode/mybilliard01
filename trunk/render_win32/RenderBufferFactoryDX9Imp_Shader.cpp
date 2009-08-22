#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShader * RenderBufferFactoryDX9Imp::createEffectShader( wstring filename )
{
    EffectShaderDX9 * newEffect = findAlreadyCreatedEffectShader( filename );
    if( NULL == newEffect ) newEffect = new EffectShaderDX9Imp( getD3D9Device(), filename, d3dEffectPool_ );
    if( NULL == newEffect ) return NULL;

    const bool bAcquired = newEffect->acquireResource();
    assert( bAcquired );

    if( bAcquired ) pushBackToActiveQueue( E_EFFECT_SHADERS, newEffect );
    else pushBackToReadyQueue( E_EFFECT_SHADERS, newEffect );

    return newEffect;
}

EffectShaderDX9 * RenderBufferFactoryDX9Imp::findAlreadyCreatedEffectShader( wstring filename ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i ) {
        MY_FOR_EACH( ReleasableResources, iter, resources_[ E_EFFECT_SHADERS ][ i ] ) {
            EffectShaderDX9Imp * const effectShader = dynamic_cast< EffectShaderDX9Imp * >( &**iter );
            if( effectShader->getFilename() != filename ) continue;
            return new EffectShaderDX9Imp( *effectShader );
        }
    }

    return NULL;
}

}
