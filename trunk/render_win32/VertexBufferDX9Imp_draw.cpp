#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


VertexBuffer::DrawPrimitive * VertexBufferDX9Imp::drawPrimitive() {
    return drawPrimitive_[ VERTEX_DECL_COMPLETE ].get();
}

VertexBuffer::DrawPrimitive * VertexBufferDX9Imp::drawPrimitive_positionOnly() {
    return drawPrimitive_[ VERTEX_DECL_POSITION_ONLY ].get();
}

VertexBufferDX9Imp::DrawPrimitiveImp::DrawPrimitiveImp( VertexBufferDX9Imp * parent, bool bPositionOnly )
: parent_( parent )
, bPositionOnly_( bPositionOnly )
{
    THROW_UNLESS( parent, exception() );
}

LPDIRECT3DVERTEXDECLARATION9 VertexBufferDX9Imp::DrawPrimitiveImp::getVertexDecl() {
    return ( bPositionOnly_
        ? parent_->getVertexDeclarationDX9_positionOnly()
        : parent_->getVertexDeclarationDX9() );
}

LPDIRECT3DVERTEXBUFFER9 VertexBufferDX9Imp::DrawPrimitiveImp::getVertexBuffer() {
    return parent_->getVertexBufferDX9();
}

size_t VertexBufferDX9Imp::DrawPrimitiveImp::getNumberOfVertex() {
    return parent_->getNumberOfVertex();
}

void VertexBufferDX9Imp::DrawPrimitiveImp::POINTLIST() {
    parent_->drawPrimitive( D3DPT_POINTLIST, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() );
}

void VertexBufferDX9Imp::DrawPrimitiveImp::LINELIST() {
    parent_->drawPrimitive( D3DPT_LINELIST, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() / 2 );
}

void VertexBufferDX9Imp::DrawPrimitiveImp::LINESTRIP() {
    parent_->drawPrimitive( D3DPT_LINESTRIP, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() - 1 );
}

void VertexBufferDX9Imp::DrawPrimitiveImp::TRIANGLELIST() {
    parent_->drawPrimitive( D3DPT_TRIANGLELIST, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() / 3 );
} 

void VertexBufferDX9Imp::DrawPrimitiveImp::TRIANGLESTRIP() {
    parent_->drawPrimitive( D3DPT_TRIANGLESTRIP, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() - 2 );
}

void VertexBufferDX9Imp::DrawPrimitiveImp::TRIANGLEFAN() {
    parent_->drawPrimitive( D3DPT_TRIANGLEFAN, getVertexDecl(), getVertexBuffer(), 0, getNumberOfVertex() - 2 );
}

void VertexBufferDX9Imp::drawPrimitive(
    D3DPRIMITIVETYPE primitiveType,
    LPDIRECT3DVERTEXDECLARATION9 decl, LPDIRECT3DVERTEXBUFFER9 vb,
    NxU32 startVertex, NxU32 primitiveCount )
{
    getD3D9Device()->SetStreamSource( 0, vb, 0, getSizeInByteForEachVertex() );
    getD3D9Device()->SetVertexDeclaration( decl );
    getD3D9Device()->DrawPrimitive( primitiveType, startVertex, primitiveCount );
}


}