#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


IndexBufferDX9Imp::IndexBufferDX9Imp( size_t numberOfIndex, unsigned short * indexies )
: index16_array_( indexies, indexies + numberOfIndex )
{
    if( 0 == numberOfIndex || NULL == indexies ) throw exception();
}

IndexBufferDX9Imp::IndexBufferDX9Imp( size_t numberOfIndex, unsigned int * indexies )
: index32_array_( indexies, indexies + numberOfIndex )
{
    if( 0 == numberOfIndex || NULL == indexies ) throw exception();
}

size_t IndexBufferDX9Imp::getNumberOfIndex()
{
    return max( index16_array_.size(), index32_array_.size() );    
}

size_t IndexBufferDX9Imp::getNumberOfByteForEach()
{
    return ( index16_array_.empty() ? 4 : 2 );
}


}
