#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE IndexBufferDX9 : STATIC_EXTENDS_INTERFACE( IndexBuffer ), EXTENDS_INTERFACE( ReleasableResourceDX9 )  {

    virtual size_t getSizeInByte() PURE;
    virtual size_t getNumberOfByteForEach() PURE; // 2 or 4

    virtual LPDIRECT3DINDEXBUFFER9 getIndexBufferDX9() PURE;
};


}
