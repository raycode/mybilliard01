#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


void RenderWin32DX9Imp::renderWithEffectShader( EffectShader * effect, ShaderVariable * technique, RenderEffectShader * callBack )
{
    assert( NULL != effect && NULL != technique && NULL != callBack );

    EffectShaderDX9 * const effectDX9 = static_cast< EffectShaderDX9 * >( effect );
    ShaderVariableDX9 * const techDX9 = static_cast< ShaderVariableDX9 * >( technique );

    effectDX9->setTechnique( techDX9 );

    const size_t nPass = effectDX9->begin();
    for( size_t i = 0; i < nPass; ++i ) {
        effectDX9->beginPass( i );
        callBack->display( this, i );
        effectDX9->endPass();
    }
    effectDX9->end();
}

void RenderWin32DX9Imp::setVertexShader( VertexShader * vs ) 
{
    assert( vs );
}

void RenderWin32DX9Imp::setPixelShader( PixelShader * ps )
{
    assert( ps );
}


void RenderWin32DX9Imp::drawPrimitive_POINTLIST( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_POINTLIST, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_LINELIST( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_LINELIST, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_LINESTRIP( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_LINESTRIP, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLELIST( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_TRIANGLELIST, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLESTRIP( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_TRIANGLESTRIP, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLEFAN( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    drawPrimitive( D3DPT_TRIANGLEFAN, vb, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_POINTLIST( 
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_POINTLIST, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_LINELIST(
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_LINELIST, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_LINESTRIP(
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_LINESTRIP, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLELIST(
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_TRIANGLELIST, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLESTRIP(
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_TRIANGLESTRIP, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLEFAN(
    VertexBuffer * vb, IndexBuffer * ib,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{
    drawIndexedPrimitive( D3DPT_TRIANGLEFAN, vb, ib, baseVertexIndex, minIndex, startIndex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive( D3DPRIMITIVETYPE primitiveType,
                                      VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    assert( vb );
    VertexBufferDX9 * const vbDX9 = static_cast< VertexBufferDX9 * >( vb );

    getD3D9Device()->SetStreamSource( 0, vbDX9->getVertexBufferDX9(), 0, vbDX9->getSizeInByteForEachVertex() );
    getD3D9Device()->SetVertexDeclaration( vbDX9->getVertexDeclarationDX9() );
    getD3D9Device()->DrawPrimitive( primitiveType, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawIndexedPrimitive( D3DPRIMITIVETYPE primitiveType,
                                             VertexBuffer * vb, IndexBuffer * ib,
                                             int baseVertexIndex, NxU32 minIndex,
                                             NxU32 startIndex, NxU32 primitiveCount )
{
    assert( vb && ib );
    VertexBufferDX9 * const vbDX9 = static_cast< VertexBufferDX9 * >( vb );
    IndexBufferDX9 * const ibDX9 = static_cast< IndexBufferDX9 * >( ib );

    getD3D9Device()->SetStreamSource( 0, vbDX9->getVertexBufferDX9(), 0, vbDX9->getSizeInByteForEachVertex() );
    getD3D9Device()->SetVertexDeclaration( vbDX9->getVertexDeclarationDX9() );
    getD3D9Device()->SetIndices( ibDX9->getIndexBufferDX9() );
    getD3D9Device()->DrawIndexedPrimitive( primitiveType, baseVertexIndex, minIndex, ibDX9->getNumberOfIndex(), startIndex, primitiveCount );
}


}