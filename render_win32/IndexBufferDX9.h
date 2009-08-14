#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ IndexBufferDX9 : EXTENDS_INTERFACE_( IndexBuffer ) {
public:
    virtual void setIndexBufferDX9( LPDIRECT3DINDEXBUFFER9 ) = 0;
    virtual LPDIRECT3DINDEXBUFFER9 getIndexBufferDX9() = 0;

    virtual void writeOntoDevice( DWORD lockingFlags ) = 0;
    virtual void releaseIndexBufferDX9() = 0;
};


}
