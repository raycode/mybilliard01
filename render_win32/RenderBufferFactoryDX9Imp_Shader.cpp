#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


EffectShader * RenderBufferFactoryDX9Imp::createEffectShader( wstring filename )
{
    EffectShaderDX9 * const newEffect = new EffectShaderDX9Imp( getD3D9Device(), filename );
    if( NULL == newEffect ) return NULL;

    const bool bAcquired = newEffect->acquireResource();
    if( false == bAcquired ) return NULL;

    pushBackToActiveQueue( E_EFFECT_SHADERS, newEffect );
    return newEffect;
}

VertexShader * RenderBufferFactoryDX9Imp::createVertexShader_1_1( wstring filename, wstring entry ) 
{
    return NULL;
}

VertexShader * RenderBufferFactoryDX9Imp::createVertexShader_2_0( wstring filename, wstring entry ) 
{
    return NULL;
}

VertexShader * RenderBufferFactoryDX9Imp::createVertexShader_2_0_sw( wstring filename, wstring entry ) 
{
    return NULL;
}

PixelShader * RenderBufferFactoryDX9Imp::createPixelShader_2_0( wstring filename, wstring entry ) 
{
    return NULL;
}

PixelShader * RenderBufferFactoryDX9Imp::createPixelShader_2_sw( wstring filename, wstring entry ) 
{
    return NULL;
}



}
