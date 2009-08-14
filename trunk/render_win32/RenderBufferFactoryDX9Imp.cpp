#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderBufferFactoryDX9Imp::RenderBufferFactoryDX9Imp( IDirect3DDevice9 * d3dDevice )
: d3dDevice_( d3dDevice )
{    
    if( NULL == d3dDevice ) throw exception();
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_static( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    staticVertices_.push_back( VertexBufferDX9Ptr( vbo ) );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    dynamicVertices_.push_back( VertexBufferDX9Ptr( vbo ) );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    streamVertices_.push_back( VertexBufferDX9Ptr( vbo ) );
    return vbo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    staticIndexies_.push_back( IndexBufferDX9Ptr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    dynamicIndexies_.push_back( IndexBufferDX9Ptr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    streamIndexies_.push_back( IndexBufferDX9Ptr( ibo ) );
    return ibo;
}

Surface * RenderBufferFactoryDX9Imp::getBackBuffer( size_t whichBackBuffer ) {
    IDirect3DSurface9 * newDXSurface;
    const HRESULT hr = getD3D9Device()->GetBackBuffer( 0, whichBackBuffer, D3DBACKBUFFER_TYPE_MONO, &newDXSurface );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"RenderWin32DX9Imp::getBackBuffer", hr );
        return NULL;
    }

    SurfaceDX9Imp * const newSurface = new SurfaceDX9Imp( newDXSurface );
    surfaces_.push_back( SurfaceDX9ImpPtr( newSurface ) );  
    return newSurface;
}

bool RenderBufferFactoryDX9Imp::releaseVertexBuffer( VertexBuffer * vertexBuffer ) {
    if( true == release( vertexBuffer, staticVertices_ ) ) return true;
    if( true == release( vertexBuffer, dynamicVertices_ ) ) return true;
    if( true == release( vertexBuffer, streamVertices_ ) ) return true;
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseIndexBuffer( IndexBuffer * indexBuffer ) {
    if( true == release( indexBuffer, staticIndexies_ ) ) return true;
    if( true == release( indexBuffer, dynamicIndexies_ ) ) return true;
    if( true == release( indexBuffer, streamIndexies_ ) ) return true;
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseSurface( Surface * surface ) {
    return release( surface, surfaces_ );
}

void RenderBufferFactoryDX9Imp::init( RenderBufferFactory * )
{
    uploadVertexBuffers( streamVertices_, D3DUSAGE_DYNAMIC, D3DPOOL_SYSTEMMEM, 0 );
    uploadIndexBuffers( streamIndexies_, D3DUSAGE_DYNAMIC, D3DPOOL_SYSTEMMEM, 0 );
}

void RenderBufferFactoryDX9Imp::displayReset( RenderBufferFactory *, int x, int y, int width, int height )
{
    uploadVertexBuffers( staticVertices_, D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );
    uploadIndexBuffers( staticIndexies_, D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );

    uploadVertexBuffers( dynamicVertices_, D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );
    uploadIndexBuffers( dynamicIndexies_, D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );
}

void RenderBufferFactoryDX9Imp::displayLost( RenderBufferFactory * )
{
    MY_FOR_EACH( StaticVertices, iter, staticVertices_ ) (&**iter)->releaseVertexBufferDX9();
    MY_FOR_EACH( StaticIndexies, iter, staticIndexies_ ) (&**iter)->releaseIndexBufferDX9();

    MY_FOR_EACH( DynamicVertices, iter, dynamicVertices_ ) (&**iter)->releaseVertexBufferDX9();
    MY_FOR_EACH( DynamicIndexies, iter, dynamicIndexies_ ) (&**iter)->releaseIndexBufferDX9();
}

void RenderBufferFactoryDX9Imp::destroy( RenderBufferFactory * )
{
    MY_FOR_EACH( StreamVertices, iter, streamVertices_ ) (&**iter)->releaseVertexBufferDX9();
    MY_FOR_EACH( StreamIndexies, iter, streamIndexies_ ) (&**iter)->releaseIndexBufferDX9();
}

void RenderBufferFactoryDX9Imp::uploadVertexBuffers( const list< VertexBufferDX9Ptr > & among, DWORD usage, D3DPOOL pool, DWORD lockingFlags )
{
    MY_FOR_EACH( list< VertexBufferDX9Ptr >, iter, among ) {
        VertexBufferDX9 * const vertexBuffer = &**iter;

        const size_t sizeInByte = vertexBuffer->getSizeInByte();
        const unsigned long fvf = vertexBuffer->getFVF();

        LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9 = NULL;
        const HRESULT hr = getD3D9Device()->CreateVertexBuffer( sizeInByte, usage, fvf, pool, &vertexBufferDX9, NULL );
        if( FAILED( hr ) )
        {
            DXUT_ERR( L"RenderBufferFactoryDX9Imp::uploadVertexBuffers", hr );
            continue;
        }

        vertexBuffer->setVertexBufferDX9( vertexBufferDX9 );
        vertexBuffer->writeOntoDevice( lockingFlags );
    }
}

void RenderBufferFactoryDX9Imp::uploadIndexBuffers( const list< IndexBufferDX9Ptr > & among, DWORD usage, D3DPOOL pool, DWORD lockingFlags )
{
    MY_FOR_EACH( list< IndexBufferDX9Ptr >, iter, among ) {
        IndexBufferDX9 * const indexBuffer = &**iter;

        const size_t sizeInByte = indexBuffer->getSizeInByte();
        const D3DFORMAT fmt = (( indexBuffer->getNumberOfByteForEach() == 4 ) ? D3DFMT_INDEX32 : D3DFMT_INDEX16 );

        LPDIRECT3DINDEXBUFFER9 indexBufferDX9 = NULL;
        const HRESULT hr = getD3D9Device()->CreateIndexBuffer( sizeInByte, usage, fmt, pool, &indexBufferDX9, NULL );
        if( FAILED( hr ) )
        {
            DXUT_ERR( L"RenderBufferFactoryDX9Imp::uploadIndexBuffers", hr );
            continue;
        }

        indexBuffer->setIndexBufferDX9( indexBufferDX9 );
        indexBuffer->writeOntoDevice( lockingFlags );
    }
}

IDirect3DDevice9 * RenderBufferFactoryDX9Imp::getD3D9Device() {
    return d3dDevice_;
}


}
