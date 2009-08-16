#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderBufferFactoryDX9Imp::RenderBufferFactoryDX9Imp( LPDIRECT3DDEVICE9 d3dDevice )
: d3dDevice_( d3dDevice )
, bNeedToUpdate_( false )
{    
    if( NULL == d3dDevice ) throw exception();
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_static( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    staticVertices_[ EREADY_QUEUE ].push_back( VertexBufferDX9Ptr( vbo ) );
    bNeedToUpdate_ = true;
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    dynamicVertices_[ EREADY_QUEUE ].push_back( VertexBufferDX9Ptr( vbo ) );
    bNeedToUpdate_ = true;
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    streamVertices_[ EREADY_QUEUE ].push_back( VertexBufferDX9Ptr( vbo ) );
    bNeedToUpdate_ = true;
    return vbo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    staticIndexies_[ EREADY_QUEUE ].push_back( IndexBufferDX9Ptr( ibo ) );
    bNeedToUpdate_ = true;
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    dynamicIndexies_[ EREADY_QUEUE ].push_back( IndexBufferDX9Ptr( ibo ) );
    bNeedToUpdate_ = true;
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    streamIndexies_[ EREADY_QUEUE ].push_back( IndexBufferDX9Ptr( ibo ) );
    bNeedToUpdate_ = true;
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
    surfaces_[ EACTIVE_QUEUE ].push_back( SurfaceDX9ImpPtr( newSurface ) );  
    return newSurface;
}

Texture * RenderBufferFactoryDX9Imp::createTexture( wstring filename )
{
    return NULL;
}

bool RenderBufferFactoryDX9Imp::releaseEffectShader( EffectShader * effectShader )
{
    return release( effectShader, effectShaders_ );
}

bool RenderBufferFactoryDX9Imp::releaseVertexShader( VertexShader *)
{
    return false;
}

bool RenderBufferFactoryDX9Imp::releasePixelShader( PixelShader *)
{
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseVertexBuffer( VertexBuffer * vertexBuffer ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i ) {
        if( release( vertexBuffer, staticVertices_[ i ] ) ) return true;
        if( release( vertexBuffer, dynamicVertices_[ i ] ) ) return true;
        if( release( vertexBuffer, streamVertices_[ i ] ) ) return true;
    }
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseIndexBuffer( IndexBuffer * indexBuffer ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i ) {
        if( release( indexBuffer, staticIndexies_[ i ] ) ) return true;
        if( release( indexBuffer, dynamicIndexies_[ i ] ) ) return true;
        if( release( indexBuffer, streamIndexies_[ i ] ) ) return true;
    }
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseSurface( Surface * surface ) {
    for( size_t i = 0; i < SIZE_OF_QUEUE; ++i ) {
        if( release( surface, surfaces_[ i ] ) ) return true;
    }
    return false;
}

bool RenderBufferFactoryDX9Imp::releaseTexture( Texture * ) {
    return false;
}

void RenderBufferFactoryDX9Imp::init( RenderBufferFactory * )
{
    uploadSteamBuffers();
}

void RenderBufferFactoryDX9Imp::displayReset( int x, int y, int width, int height )
{
    uploadStaticBuffers();
    uploadDynamicBuffers();
    uploadSteamBuffers();
}

void RenderBufferFactoryDX9Imp::update( RenderBufferFactory *, float elapsedTime )
{
    if( false == bNeedToUpdate_ ) return;
    bNeedToUpdate_ = false;

    uploadStaticBuffers();
    uploadDynamicBuffers();
    uploadSteamBuffers();
}

void RenderBufferFactoryDX9Imp::displayLost()
{
    releaseStaticBuffers();
    releaseDynamicBuffers();
}

void RenderBufferFactoryDX9Imp::destroy()
{
    releaseStaticBuffers();
    releaseDynamicBuffers();
    releaseStreamBuffers();
}

void RenderBufferFactoryDX9Imp::uploadStaticBuffers()
{
    uploadVertexBuffers( staticVertices_[ EREADY_QUEUE ], D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );
    uploadIndexBuffers( staticIndexies_[ EREADY_QUEUE ], D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );

    staticVertices_[ EACTIVE_QUEUE ].merge( staticVertices_[ EREADY_QUEUE ] );
    staticIndexies_[ EACTIVE_QUEUE ].merge( staticIndexies_[ EREADY_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::uploadDynamicBuffers()
{
    uploadVertexBuffers( dynamicVertices_[ EREADY_QUEUE ], D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );
    uploadIndexBuffers( dynamicIndexies_[ EREADY_QUEUE ], D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );

    dynamicVertices_[ EACTIVE_QUEUE ].merge( dynamicVertices_[ EREADY_QUEUE ] );
    dynamicIndexies_[ EACTIVE_QUEUE ].merge( dynamicIndexies_[ EREADY_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::uploadSteamBuffers()
{
    uploadVertexBuffers( streamVertices_[ EREADY_QUEUE ], D3DUSAGE_DYNAMIC, D3DPOOL_SYSTEMMEM, 0 );
    uploadIndexBuffers( streamIndexies_[ EREADY_QUEUE ], D3DUSAGE_DYNAMIC, D3DPOOL_SYSTEMMEM, 0 );

    streamVertices_[ EACTIVE_QUEUE ].merge( streamVertices_[ EREADY_QUEUE ] );
    streamIndexies_[ EACTIVE_QUEUE ].merge( streamIndexies_[ EREADY_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::releaseStaticBuffers()
{
    MY_FOR_EACH( StaticVertices, iter, staticVertices_[ EACTIVE_QUEUE ] ) {
        (&**iter)->releaseVertexBufferDX9();
        (&**iter)->releaseVertexDeclarationDX9();
    }
    MY_FOR_EACH( StaticIndexies, iter, staticIndexies_[ EACTIVE_QUEUE ] )
        (&**iter)->releaseIndexBufferDX9();

    staticVertices_[ EREADY_QUEUE ].merge( staticVertices_[ EACTIVE_QUEUE ] );
    staticIndexies_[ EREADY_QUEUE ].merge( staticIndexies_[ EACTIVE_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::releaseDynamicBuffers()
{
    MY_FOR_EACH( DynamicVertices, iter, dynamicVertices_[ EACTIVE_QUEUE ] ) {
        (&**iter)->releaseVertexBufferDX9();
        (&**iter)->releaseVertexDeclarationDX9();
    }
    MY_FOR_EACH( DynamicIndexies, iter, dynamicIndexies_[ EACTIVE_QUEUE ] )
        (&**iter)->releaseIndexBufferDX9();

    dynamicVertices_[ EREADY_QUEUE ].merge( dynamicVertices_[ EACTIVE_QUEUE ] );
    dynamicIndexies_[ EREADY_QUEUE ].merge( dynamicIndexies_[ EACTIVE_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::releaseStreamBuffers()
{
    MY_FOR_EACH( StreamVertices, iter, streamVertices_[ EACTIVE_QUEUE ] ) {
        (&**iter)->releaseVertexBufferDX9();
        (&**iter)->releaseVertexDeclarationDX9();
    }
    MY_FOR_EACH( StreamIndexies, iter, streamIndexies_[ EACTIVE_QUEUE ] )
        (&**iter)->releaseIndexBufferDX9();

    streamVertices_[ EREADY_QUEUE ].merge( streamVertices_[ EACTIVE_QUEUE ] );
    streamIndexies_[ EREADY_QUEUE ].merge( streamIndexies_[ EACTIVE_QUEUE ] );
}

void RenderBufferFactoryDX9Imp::uploadVertexBuffers( const list< VertexBufferDX9Ptr > & among, DWORD usage, D3DPOOL pool, DWORD lockingFlags )
{
    MY_FOR_EACH( list< VertexBufferDX9Ptr >, iter, among ) {
        VertexBufferDX9 * const vertexBuffer = &**iter;

        const D3DVERTEXELEMENT9 * const vertexElement = vertexBuffer->getVertexElement();
        IDirect3DVertexDeclaration9 * vertexDecl = NULL;
        const HRESULT hr1 = getD3D9Device()->CreateVertexDeclaration( vertexElement, &vertexDecl );
        if( FAILED( hr1 ) )
        {
            DXUT_ERR( L"RenderBufferFactoryDX9Imp::uploadVertexBuffers", hr1 );
            continue;
        }
        vertexBuffer->setVertexDeclarationDX9( vertexDecl );

        const size_t sizeInByte = vertexBuffer->getSizeInByteForTotal();
        LPDIRECT3DVERTEXBUFFER9 vertexBufferDX9 = NULL;
        const HRESULT hr2 = getD3D9Device()->CreateVertexBuffer( sizeInByte, usage, 0, pool, &vertexBufferDX9, NULL );
        if( FAILED( hr2 ) )
        {
            DXUT_ERR( L"RenderBufferFactoryDX9Imp::uploadVertexBuffers", hr2 );
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

LPDIRECT3DDEVICE9 RenderBufferFactoryDX9Imp::getD3D9Device() {
    return d3dDevice_;
}


}
