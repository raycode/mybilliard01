#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


IndexBufferDX9Imp::IndexBufferDX9Imp( size_t numberOfIndex, unsigned int * indexies )
: indexBufferDX9_( NULL )
{
    if( 0 == numberOfIndex || NULL == indexies ) throw exception();

    const bool bShort = ( numberOfIndex < (1 << 16) );

    if( bShort )
        index16_array_ = Index16_Array( indexies, indexies + numberOfIndex );
    else
        index32_array_ = Index32_Array( indexies, indexies + numberOfIndex );

    assert( getNumberOfIndex() == numberOfIndex );
}

size_t IndexBufferDX9Imp::getNumberOfIndex()
{
    return max( index16_array_.size(), index32_array_.size() );    
}

size_t IndexBufferDX9Imp::getNumberOfByteForEach()
{
    return ( index16_array_.empty() ? 4 : 2 );
}

void IndexBufferDX9Imp::setIndexBufferDX9( LPDIRECT3DINDEXBUFFER9 ) {

}

void IndexBufferDX9Imp::writeOntoDevice( DWORD lockingFlags ) {

}

void IndexBufferDX9Imp::releaseIndexBufferDX9() {

}

LPDIRECT3DINDEXBUFFER9 IndexBufferDX9Imp::getIndexBufferDX9() {
    return indexBufferDX9_;
}


}
