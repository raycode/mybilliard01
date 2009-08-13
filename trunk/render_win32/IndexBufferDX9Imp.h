#pragma once
namespace my_render_win32_dx9_imp {


class IndexBufferDX9Imp : IMPLEMENTS_( IndexBufferDX9 ) {
public: // from IndexBuffer
    virtual size_t getNumberOfIndex() OVERRIDE;
    virtual size_t getNumberOfByteForEach() OVERRIDE; // 2 or 4

public:
    IndexBufferDX9Imp( size_t numberOfIndex, unsigned short * indexies );
    IndexBufferDX9Imp( size_t numberOfIndex, unsigned int * indexies );

private:
    typedef vector< unsigned short > Index16_Array;
    Index16_Array index16_array_;

    typedef vector< unsigned int > Index32_Array;
    Index32_Array index32_array_;
};


}
