#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


struct VertexBufferDX9Imp::Pimpl {
    static int updateOffset( StorageContainer_Array & group, int offset ) {

        MY_FOR_EACH_MODIFY( StorageContainer_Array, iter, group ) {
            iter->setOffset( offset );
            offset += (WORD) ( iter->empty() ? 0 : iter->sizeInByteForEach() );
        }
        return offset;
    }

    static void writeOntoBuffer( float * buffer, StorageContainer_Array & group, size_t step ) {

        MY_FOR_EACH_MODIFY( StorageContainer_Array, iter, group ) {
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
            tmp.Type = (BYTE) iter->getDeclarationType();
            tmp.Method = D3DDECLMETHOD_DEFAULT;
            tmp.Usage = Usage_;
            tmp.UsageIndex = (BYTE) iter->getUsageIndex();

            vertexElements.push_back( tmp );
        }
    }

};


VertexBufferDX9Imp::VertexBufferDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t howMany, const float * source, DWORD usage, D3DPOOL pool, DWORD lockingFlags )
: d3d9Device_( d3d9Device )
, usage_( usage )
, pool_( pool )
, lockingFlags_( lockingFlags )
{
    if( 0 == howMany || NULL == source ) throw exception();

    storageContainer_array_[ D3DDECLUSAGE_POSITION ].push_back( StorageContainer( source, howMany, 0, D3DDECLTYPE_FLOAT3 ) );

    drawPrimitive_[ VERTEX_DECL_COMPLETE ] = DrawPrimitiveImpPtr( new DrawPrimitiveImp( this, false ) );
    drawPrimitive_[ VERTEX_DECL_POSITION_ONLY ] = DrawPrimitiveImpPtr( new DrawPrimitiveImp( this, true ) );
}

bool VertexBufferDX9Imp::acquireResource()
{
    const D3DVERTEXELEMENT9 element_positionOnly[] =
    {
        { 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
        D3DDECL_END()
    };

    LPDIRECT3DVERTEXDECLARATION9 newDecl_complete;
    const HRESULT hr1 = getD3D9Device()->CreateVertexDeclaration( getVertexElement(), &newDecl_complete );
    RETURN_FALSE_IF_FAILED( hr1, L"RenderBufferFactoryDX9Imp::acquireResource" );
    IDirect3DVertexDeclaration9Ptr decl_complete = IDirect3DVertexDeclaration9Ptr( newDecl_complete, ComReleaser< IDirect3DVertexDeclaration9 >() );

    LPDIRECT3DVERTEXDECLARATION9 newDecl_positionOnly;
    const HRESULT hr2 = getD3D9Device()->CreateVertexDeclaration( element_positionOnly, &newDecl_positionOnly );
    RETURN_FALSE_IF_FAILED( hr2, L"RenderBufferFactoryDX9Imp::acquireResource" );
    IDirect3DVertexDeclaration9Ptr decl_positionOnly = IDirect3DVertexDeclaration9Ptr( newDecl_positionOnly, ComReleaser< IDirect3DVertexDeclaration9 >() );

    LPDIRECT3DVERTEXBUFFER9 newBuffer;
    const HRESULT hr3 = getD3D9Device()->CreateVertexBuffer( getSizeInByteForTotal(), usage_, 0, pool_, &newBuffer, NULL );
    RETURN_FALSE_IF_FAILED( hr3, L"RenderBufferFactoryDX9Imp::acquireResource" );
    IDirect3DVertexBuffer9Ptr buffer = IDirect3DVertexBuffer9Ptr( newBuffer, ComReleaser< IDirect3DVertexBuffer9 >() );

    vertexDeclarationDX9_[ VERTEX_DECL_COMPLETE ] = decl_complete;
    vertexDeclarationDX9_[ VERTEX_DECL_POSITION_ONLY ] = decl_positionOnly;
    vertexBufferDX9_ = buffer;

    writeOntoDevice( lockingFlags_ );
    return true;
}

void VertexBufferDX9Imp::releaseResource()
{
    vertexBufferDX9_.reset();

    for( size_t i = 0; i < SIZE_OF_VERTEX_DECL_ENUM; ++i ) {
        vertexDeclarationDX9_[ i ].reset();
    }
}

LPDIRECT3DDEVICE9 VertexBufferDX9Imp::getD3D9Device() {
    return d3d9Device_;
}

LPDIRECT3DVERTEXDECLARATION9 VertexBufferDX9Imp::getVertexDeclarationDX9() {
    return vertexDeclarationDX9_[ VERTEX_DECL_COMPLETE ].get();
}

LPDIRECT3DVERTEXDECLARATION9 VertexBufferDX9Imp::getVertexDeclarationDX9_positionOnly() {
    return vertexDeclarationDX9_[ VERTEX_DECL_POSITION_ONLY ].get();
}


LPDIRECT3DVERTEXBUFFER9 VertexBufferDX9Imp::getVertexBufferDX9() {
    return vertexBufferDX9_.get();
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

bool VertexBufferDX9Imp::appendColor_Array( const NxU32 * source, size_t usageIndex )
{
    if( true == isUsageIndexInUse( D3DDECLUSAGE_COLOR, usageIndex ) ) return false;
    storageContainer_array_[ D3DDECLUSAGE_COLOR ].push_back( StorageContainer( source, getNumberOfVertex(), usageIndex, D3DDECLTYPE_D3DCOLOR ) );
    return true;
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



}
