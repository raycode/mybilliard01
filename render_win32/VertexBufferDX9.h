#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ VertexBufferDX9 : EXTENDS_INTERFACE_STATIC_( VertexBuffer ) {
public:
    virtual size_t getSizeInByteForTotal() = 0;
    virtual size_t getSizeInByteForEachVertex() = 0;

    virtual D3DVERTEXELEMENT9 * getVertexElement() = 0;

    virtual void setVertexDeclarationDX9( LPDIRECT3DVERTEXDECLARATION9 ) = 0;
    virtual LPDIRECT3DVERTEXDECLARATION9 getVertexDeclarationDX9() = 0;
    virtual void releaseVertexDeclarationDX9() = 0;

    virtual void setVertexBufferDX9( LPDIRECT3DVERTEXBUFFER9 ) = 0;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() = 0;
    virtual void releaseVertexBufferDX9() = 0;

    virtual void writeOntoDevice( DWORD lockingFlags ) = 0;
};


}
