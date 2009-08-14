#pragma once
namespace my_render_win32_dx9_imp {


class IndexBufferDX9Imp : IMPLEMENTS_( IndexBufferDX9 ) {
public: // from IndexBuffer
    virtual size_t getNumberOfIndex() OVERRIDE;

public: // from IndexBufferDX9
    virtual size_t getSizeInByte() OVERRIDE;
    virtual size_t getNumberOfByteForEach() OVERRIDE; // 2 or 4

    virtual void setIndexBufferDX9( LPDIRECT3DINDEXBUFFER9 ) OVERRIDE;
    virtual LPDIRECT3DINDEXBUFFER9 getIndexBufferDX9() OVERRIDE;

    virtual void writeOntoDevice( DWORD lockingFlags ) OVERRIDE;
    virtual void releaseIndexBufferDX9() OVERRIDE;

public:
    IndexBufferDX9Imp( size_t numberOfIndex, const unsigned int * indexies );
    ~IndexBufferDX9Imp();

private:
    typedef vector< unsigned short > Index16_Array;
    Index16_Array index16_array_;

    typedef vector< unsigned int > Index32_Array;
    Index32_Array index32_array_;

private:
    LPDIRECT3DINDEXBUFFER9 indexBufferDX9_;

    MY_UNIT_TEST_BACKDOOR;
};


}
