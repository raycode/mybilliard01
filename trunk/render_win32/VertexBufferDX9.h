#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ VertexBufferDX9 : EXTENDS_INTERFACE_( VertexBuffer ) {
public:
    virtual size_t getSizeInByte() = 0;
    virtual unsigned long getFVF() = 0;
    virtual size_t getSizeInByteForEachVertex() = 0;

    virtual void setVertexBufferDX9( LPDIRECT3DVERTEXBUFFER9 ) = 0;
    virtual LPDIRECT3DVERTEXBUFFER9 getVertexBufferDX9() = 0;

    virtual void writeOntoDevice( DWORD lockingFlags ) = 0;
    virtual void releaseVertexBufferDX9() = 0;
};


}
