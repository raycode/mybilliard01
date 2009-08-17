#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE VertexBufferDX9 : STATIC_EXTENDS_INTERFACE( VertexBuffer ), EXTENDS_INTERFACE( ReleasableResourceDX9 )  {

    virtual size_t getSizeInByteForEachVertex() = 0;
    virtual LPDIRECT3DVERTEXDECLARATION9 getVertexDeclarationDX9() = 0;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() = 0;

};


}
