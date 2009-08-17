#pragma once
namespace my_render_win32_dx9_imp {


class IndexBufferDX9Imp : IMPLEMENTS_INTERFACE( IndexBufferDX9 ) {
public: // from IndexBuffer
    virtual size_t getNumberOfIndex() OVERRIDE;

public: // from IndexBufferDX9
    virtual size_t getSizeInByte() OVERRIDE;
    virtual size_t getNumberOfByteForEach() OVERRIDE; // 2 or 4

    virtual LPDIRECT3DINDEXBUFFER9 getIndexBufferDX9() OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    IndexBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device , size_t numberOfIndex, const unsigned int * indexies, DWORD usage, D3DPOOL pool, DWORD lockingFlags  );
    ~IndexBufferDX9Imp();

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

    void writeOntoDevice( DWORD lockingFlags );

private:
    typedef vector< unsigned short > Index16_Array;
    Index16_Array index16_array_;

    typedef vector< unsigned int > Index32_Array;
    Index32_Array index32_array_;

    DWORD usage_;
    D3DPOOL pool_;
    DWORD lockingFlags_;

private:
    LPDIRECT3DDEVICE9 d3d9Device_;
    LPDIRECT3DINDEXBUFFER9 indexBufferDX9_;

    MY_UNIT_TEST_BACKDOOR;
};


}
