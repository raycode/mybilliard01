#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


IndexBufferDX9Imp::IndexBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device , size_t numberOfIndex, const unsigned int * indexies, DWORD usage, D3DPOOL pool, DWORD lockingFlags  )
    : d3d9Device_( d3d9Device )
    , usage_( usage )
    , pool_( pool )
    , lockingFlags_( lockingFlags )
    , indexBufferDX9_( NULL )
{
    if( 0 == numberOfIndex || NULL == indexies ) throw exception();

    const bool bShort = ( numberOfIndex < (1 << 16) );

    if( bShort )
        index16_array_ = Index16_Array( indexies, indexies + numberOfIndex );
    else
        index32_array_ = Index32_Array( indexies, indexies + numberOfIndex );

    assert( getNumberOfIndex() == numberOfIndex );
}

IndexBufferDX9Imp::~IndexBufferDX9Imp() {
    releaseResource();
}

bool IndexBufferDX9Imp::acquireResource()
{
    releaseResource();

    const D3DFORMAT fmt = (( getNumberOfByteForEach() == 4 ) ? D3DFMT_INDEX32 : D3DFMT_INDEX16 );

    const HRESULT hr = getD3D9Device()->CreateIndexBuffer( getSizeInByte(), usage_, fmt, pool_, &indexBufferDX9_, NULL );
    if( FAILED( hr ) )
    {
        DXUT_ERR( L"RenderBufferFactoryDX9Imp::uploadIndexBuffers", hr );
        return false;
    }

    writeOntoDevice( lockingFlags_ );
    return true;
}

void IndexBufferDX9Imp::releaseResource() {
    SAFE_RELEASE( indexBufferDX9_ );
}

LPDIRECT3DDEVICE9 IndexBufferDX9Imp::getD3D9Device() {
    return d3d9Device_;
}

size_t IndexBufferDX9Imp::getNumberOfIndex()
{
    return max( index16_array_.size(), index32_array_.size() );    
}

size_t IndexBufferDX9Imp::getNumberOfByteForEach()
{
    return ( index16_array_.empty() ? 4 : 2 );
}

size_t IndexBufferDX9Imp::getSizeInByte() {
    return getNumberOfIndex() * getNumberOfByteForEach();
}

LPDIRECT3DINDEXBUFFER9 IndexBufferDX9Imp::getIndexBufferDX9() {
    return indexBufferDX9_;
}

void IndexBufferDX9Imp::writeOntoDevice( DWORD lockingFlags ) {
    float * indexies;
    const HRESULT hr = indexBufferDX9_->Lock( 0, getSizeInByte(), (void**) &indexies, lockingFlags );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"IndexBufferDX9Imp::writeOntoDevice", hr );
        return;
    }

    memcpy( indexies, (BYTE*) &(index16_array_[0]), index16_array_.size() * sizeof( Index16_Array::value_type ) );
    memcpy( indexies, (BYTE*) &(index32_array_[0]), index32_array_.size() * sizeof( Index32_Array::value_type ) );

    indexBufferDX9_->Unlock();
}



}
