#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


void VertexBufferDX9Imp::drawPrimitive_POINTLIST() {
    drawPrimitive( D3DPT_POINTLIST, getVertexBufferDX9(), 0, getNumberOfVertex() );
}
void VertexBufferDX9Imp::drawPrimitive_LINELIST() {
    drawPrimitive( D3DPT_LINELIST, getVertexBufferDX9(), 0, getNumberOfVertex() / 2 );
}
void VertexBufferDX9Imp::drawPrimitive_LINESTRIP() {
    drawPrimitive( D3DPT_LINESTRIP, getVertexBufferDX9(), 0, getNumberOfVertex() - 1 );
}
void VertexBufferDX9Imp::drawPrimitive_TRIANGLELIST() {
    drawPrimitive( D3DPT_TRIANGLELIST, getVertexBufferDX9(), 0, getNumberOfVertex() /3 );
}
void VertexBufferDX9Imp::drawPrimitive_TRIANGLESTRIP() {
    drawPrimitive( D3DPT_TRIANGLESTRIP, getVertexBufferDX9(), 0, getNumberOfVertex() - 2 );
}
void VertexBufferDX9Imp::drawPrimitive_TRIANGLEFAN() {
    drawPrimitive( D3DPT_TRIANGLEFAN, getVertexBufferDX9(), 0, getNumberOfVertex() - 2 );
}

void VertexBufferDX9Imp::drawPrimitive( D3DPRIMITIVETYPE primitiveType,
                                      LPDIRECT3DVERTEXBUFFER9 vb, NxU32 startVertex, NxU32 primitiveCount )
{
    getD3D9Device()->SetStreamSource( 0, vb, 0, getSizeInByteForEachVertex() );
    getD3D9Device()->SetVertexDeclaration( getVertexDeclarationDX9() );
    getD3D9Device()->DrawPrimitive( primitiveType, startVertex, primitiveCount );
}


}