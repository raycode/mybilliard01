#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShader * RenderBufferFactoryDX9Imp::createEffectShader( wstring filename )
{
    EffectShaderDX9 * const newEffect = new EffectShaderDX9Imp( getD3D9Device(), filename, d3dEffectPool_ );
    if( NULL == newEffect ) return NULL;

    const bool bAcquired = newEffect->acquireResource();
    assert( bAcquired );

    if( bAcquired ) pushBackToActiveQueue( E_EFFECT_SHADERS, newEffect );
    else pushBackToReadyQueue( E_EFFECT_SHADERS, newEffect );

    return newEffect;
}



}
