#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE VertexBufferDX9 : EXTENDS_INTERFACE( VertexBuffer ), EXTENDS_INTERFACE( ReleasableResourceDX9 )  {

    virtual size_t getSizeInByteForEachVertex() PURE;
    virtual LPDIRECT3DVERTEXDECLARATION9 getVertexDeclarationDX9() PURE;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() PURE;

};


}
