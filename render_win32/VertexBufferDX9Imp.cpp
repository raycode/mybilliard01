#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


struct VertexBufferDX9Imp::Pimpl {
    static int updateOffset( StorageContainer_Array & group, int offset ) {

        MY_FOR_EACH_MOD( StorageContainer_Array, iter, group ) {
            iter->setOffset( offset );
            offset += (WORD) ( iter->empty() ? 0 : iter->sizeInByteForEach() );
        }
        return offset;
    }

    static void writeOntoBuffer( float * buffer, StorageContainer_Array & group, size_t step ) {

        MY_FOR_EACH_MOD( StorageContainer_Array, iter, group ) {
            iter->copyOntoBuffer( buffer, step );
        }
    }

    template< int Usage_ >
    static void getVertexDeclaration( StorageContainer_Array * storages, vector< D3DVERTEXELEMENT9 > & vertexElements )
    {
        MY_FOR_EACH( StorageContainer_Array, iter, storages[ Usage_ ] ) {
            if( iter->empty() ) continue;

            D3DVERTEXELEMENT9 tmp;
            tmp.Stream = 0;
            tmp.Offset = (WORD) iter->getOffset();
            tmp.Method = D3DDECLMETHOD_DEFAULT;
            tmp.Usage = Usage_;
            tmp.UsageIndex = (BYTE) iter->getUsageIndex();

            vertexElements.push_back( tmp );
        }
    }

};


VertexBufferDX9Imp::VertexBufferDX9Imp( size_t howMany, const float * source )
: vertexBufferDX9_( NULL )
, vertexDeclarationDX9_( NULL )
{
    if( 0 == howMany || NULL == source ) throw exception();

    storageContainer_array_[ D3DDECLUSAGE_POSITION ].push_back( StorageContainer( source, howMany, 0, D3DDECLTYPE_FLOAT3 ) );
}

VertexBufferDX9Imp::~VertexBufferDX9Imp()
{
    releaseVertexBufferDX9();
    releaseVertexDeclarationDX9();
}


size_t VertexBufferDX9Imp::getNumberOfVertex()
{
    return storageContainer_array_[ D3DDECLUSAGE_POSITION ][0].v.size();
}

bool VertexBufferDX9Imp::appendTexCoord1D_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TEXCOORD, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT1 ) );
    return true;
}

bool VertexBufferDX9Imp::appendTexCoord2D_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TEXCOORD, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT2 ) );
    return true;
}

bool VertexBufferDX9Imp::appendTexCoord3D_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TEXCOORD, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT3 ) );
    return true;
}

bool VertexBufferDX9Imp::appendTexCoord4D_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TEXCOORD, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT4 ) );
    return true;
}

bool VertexBufferDX9Imp::appendNormal_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_NORMAL, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_NORMAL ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT3 ) );
    return true;
}

bool VertexBufferDX9Imp::appendBinormal_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_BINORMAL, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_BINORMAL ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT3 ) );
    return true;
}

bool VertexBufferDX9Imp::appendTangent_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TANGENT, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TANGENT ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT3 ) );
    return true;
}

bool VertexBufferDX9Imp::appendUV_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_TEXCOORD, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_FLOAT3 ) );
    return true;
}

bool VertexBufferDX9Imp::appendColor_Array( const float * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_COLOR, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_COLOR ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_D3DCOLOR ) );
    return true;
}

void VertexBufferDX9Imp::setVertexBufferDX9( LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9 )
{
    vertexBufferDX9_ = vertexBufferDX9;
}

LPDIRECT3DVERTEXBUFFER9 VertexBufferDX9Imp::getVertexBufferDX9() {
    return vertexBufferDX9_;
}

bool VertexBufferDX9Imp::isUsageIndexInUse( int usage, size_t usageIndex ) {
    MY_FOR_EACH( StorageContainer_Array, iter, storageContainer_array_[ usage ] ) {
        if( iter->empty() ) continue;
        if( iter->getUsageIndex() == usageIndex ) return true;
    }
    return false;
}

void VertexBufferDX9Imp::writeOntoDevice( DWORD lockingFlags )
{
    float * buffer;
    const HRESULT hr = vertexBufferDX9_->Lock( 0, getSizeInByteForTotal(), (void**) &buffer, lockingFlags );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"VertexBufferDX9Imp::writeOntoDevice", hr );
        return;
    }

    const size_t step = updateOffset();
    writeOntoBuffer( buffer, step );

    vertexBufferDX9_->Unlock();
}

size_t VertexBufferDX9Imp::updateOffset()
{
    int offset = 0;
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_POSITION ], offset );
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ], offset );
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_NORMAL ], offset );
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_BINORMAL ], offset );
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_TANGENT ], offset );
    offset = Pimpl::updateOffset( storageContainer_array_[ D3DDECLUSAGE_COLOR ], offset );
    return offset;
}

void VertexBufferDX9Imp::writeOntoBuffer( float * buffer, size_t step )
{
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_POSITION ], step );
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_TEXCOORD ], step );
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_NORMAL ], step );
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_BINORMAL ], step );
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_TANGENT ], step );
    Pimpl::writeOntoBuffer( buffer, storageContainer_array_[ D3DDECLUSAGE_COLOR ], step );
}

void VertexBufferDX9Imp::releaseVertexBufferDX9()
{
    SAFE_RELEASE( vertexBufferDX9_ );
}

void VertexBufferDX9Imp::releaseVertexDeclarationDX9()
{
    SAFE_RELEASE( vertexDeclarationDX9_ );
}


size_t VertexBufferDX9Imp::getSizeInByteForTotal() {
    return getSizeInByteForEachVertex() * getNumberOfVertex();
}

size_t VertexBufferDX9Imp::getSizeInByteForEachVertex() {
    return updateOffset();
}

D3DVERTEXELEMENT9 * VertexBufferDX9Imp::getVertexElement() {
    updateOffset();

    vertexElementDX9_.clear();
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_POSITION >( storageContainer_array_, vertexElementDX9_ );
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_TEXCOORD >( storageContainer_array_, vertexElementDX9_ );
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_NORMAL >( storageContainer_array_, vertexElementDX9_ );
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_BINORMAL >( storageContainer_array_, vertexElementDX9_ );
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_TANGENT >( storageContainer_array_, vertexElementDX9_ );
    Pimpl::getVertexDeclaration< D3DDECLUSAGE_COLOR >( storageContainer_array_, vertexElementDX9_ );
    
    D3DVERTEXELEMENT9 endElem = D3DDECL_END();
    vertexElementDX9_.push_back( endElem );

    return &(vertexElementDX9_[0]);
}

void VertexBufferDX9Imp::setVertexDeclarationDX9( LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationDX9 ) {
    vertexDeclarationDX9_ = vertexDeclarationDX9;
}

LPDIRECT3DVERTEXDECLARATION9 VertexBufferDX9Imp::getVertexDeclarationDX9() {
    return vertexDeclarationDX9_;
}



}
