#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


void RenderWin32DX9Imp::setVertexShader( VertexShader * ) 
{

}

void RenderWin32DX9Imp::setPixelShader( PixelShader * )
{

}

void RenderWin32DX9Imp::setEffectShader( EffectShader *, wstring technique, RenderEffectShader * callBack )
{

}


void RenderWin32DX9Imp::drawPrimitive_POINTLIST( VertexBuffer * vb, NxU32 startVertex, NxU32 primitiveCount )
{
    VertexBufferDX9 * const vbDX9 = dynamic_cast< VertexBufferDX9 * >( vb );
    if( NULL == vbDX9 ) return;

    getD3D9Device()->SetStreamSource( 0, vbDX9->getVertexBufferDX9(), 0, vbDX9->getSizeInByteForEachVertex() );
    getD3D9Device()->SetVertexDeclaration( vbDX9->getVertexDeclarationDX9() );
    getD3D9Device()->DrawPrimitive( D3DPT_POINTLIST, startVertex, primitiveCount );
}

void RenderWin32DX9Imp::drawPrimitive_LINELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawPrimitive_LINESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLELIST( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLESTRIP( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawPrimitive_TRIANGLEFAN( VertexBuffer *, NxU32 startVertex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_POINTLIST(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_LINELIST(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_LINESTRIP(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLELIST(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLESTRIP(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

void RenderWin32DX9Imp::drawIndexedPrimitive_TRIANGLEFAN(
    VertexBuffer *, IndexBuffer *,
    int baseVertexIndex, NxU32 minIndex,
    NxU32 startIndex, NxU32 primitiveCount )
{

}

}