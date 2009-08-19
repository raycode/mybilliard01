#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderBufferFactoryDX9Imp::RenderBufferFactoryDX9Imp( LPDIRECT3DDEVICE9 d3dDevice )
: d3dDevice_( d3dDevice )
, bNeedToUpdate_( false )
{    
    if( NULL == d3dDevice ) throw exception();
}

void RenderBufferFactoryDX9Imp::pushBackToReadyQueue( int resourceType, ReleasableResourceDX9 * newResource )
{
    resources_[ resourceType ][ EREADY_QUEUE ].push_back( ReleasableResourceDX9Ptr( newResource ) );
    bNeedToUpdate_ = true;
}

void RenderBufferFactoryDX9Imp::pushBackToActiveQueue( int resourceType, ReleasableResourceDX9 * newResource )
{
    resources_[ resourceType ][ EACTIVE_QUEUE ].push_back( ReleasableResourceDX9Ptr( newResource ) );
}

Surface * RenderBufferFactoryDX9Imp::getBackBuffer( size_t whichBackBuffer ) {
    IDirect3DSurface9 * newDXSurface;
    const HRESULT hr = getD3D9Device()->GetBackBuffer( 0, whichBackBuffer, D3DBACKBUFFER_TYPE_MONO, &newDXSurface );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"RenderWin32DX9Imp::getBackBuffer", hr );
        return NULL;
    }

    SurfaceDX9Imp * const newSurface = new SurfaceDX9Imp( newDXSurface );
    pushBackToActiveQueue( E_SURFACES, newSurface );
    return newSurface;
}

Texture * RenderBufferFactoryDX9Imp::createTexture( wstring filename )
{
    return NULL;
}

bool RenderBufferFactoryDX9Imp::destroy( ReleasableResourceDX9 * victim )
{
    if( NULL == victim ) return false;

    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i ) {
        for( size_t j = 0; j < SIZE_OF_QUEUE; ++j ) {
            MY_FOR_EACH( ReleasableResources, iter, resources_[ i ][ j ] ) {
                if( victim != &**iter ) continue;
                resources_[ i ][ j ].erase( iter );
                return true;
            }
        }    
    }
    return false;
}

void RenderBufferFactoryDX9Imp::destroyAll() {
    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i ) {
        for( size_t j = 0; j < SIZE_OF_QUEUE; ++j ) {
            resources_[ i ][ j ].clear();
        }    
    }
}

bool RenderBufferFactoryDX9Imp::destroyEffectShader( EffectShader * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyVertexShader( VertexShader * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyPixelShader( PixelShader * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyVertexBuffer( VertexBuffer * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyIndexBuffer( IndexBuffer * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroySurface( Surface * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

bool RenderBufferFactoryDX9Imp::destroyTexture( Texture * victim ) {
    return destroy( dynamic_cast< ReleasableResourceDX9 * >( victim ) ); 
}

void RenderBufferFactoryDX9Imp::init( RenderBufferFactory * ) {
    acquireResources();
}

void RenderBufferFactoryDX9Imp::displayReset( int x, int y, int width, int height ) {
    acquireResources();
}

void RenderBufferFactoryDX9Imp::update( RenderBufferFactory *, float elapsedTime )
{
    acquireResources();
}

void RenderBufferFactoryDX9Imp::displayLost() {
    releaseByResourceType( E_STATIC_VERTICES );
    releaseByResourceType( E_DYNAMIC_VERTICES );
    releaseByResourceType( E_STATIC_INDICES );
    releaseByResourceType( E_DYNAMIC_INDICES );
    releaseByResourceType( E_EFFECT_SHADERS );
    releaseByResourceType( E_VERTEX_SHADERS );
    releaseByResourceType( E_PIXEL_SHADERS );
    releaseByResourceType( E_SURFACES );
    releaseByResourceType( E_TEXTURE );
}

void RenderBufferFactoryDX9Imp::destroy() {
    destroyAll();
}

void RenderBufferFactoryDX9Imp::acquireResources()
{
    if( false == bNeedToUpdate_ ) return;
    bNeedToUpdate_ = false;

    for( size_t i = 0; i < SIZE_OF_RESOURCETYPES; ++i ) {
        MY_FOR_EACH( ReleasableResources, iter, resources_[ i ][ EREADY_QUEUE ] ) {
            (*iter)->acquireResource();
        }
        resources_[ i ][ EACTIVE_QUEUE ].splice( resources_[ i ][ EACTIVE_QUEUE ].end(), resources_[ i ][ EREADY_QUEUE ] );
    }
}

void RenderBufferFactoryDX9Imp::releaseByResourceType( int resourceType )
{
    MY_FOR_EACH( ReleasableResources, iter, resources_[ resourceType ][ EACTIVE_QUEUE ] ) {
        (*iter)->releaseResource();
    }
    resources_[ resourceType ][ EREADY_QUEUE ].splice( resources_[ resourceType ][ EREADY_QUEUE ].end(), resources_[ resourceType ][ EACTIVE_QUEUE ] );
    bNeedToUpdate_ = true;
}


LPDIRECT3DDEVICE9 RenderBufferFactoryDX9Imp::getD3D9Device() {
    return d3dDevice_;
}


}
