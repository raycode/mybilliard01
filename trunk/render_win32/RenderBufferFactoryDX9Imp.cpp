#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


RenderBufferFactoryDX9Imp::RenderBufferFactoryDX9Imp( IDirect3DDevice9 * d3dDevice )
: d3dDevice_( d3dDevice )
{    
    if( NULL == d3dDevice ) throw exception();
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_static( size_t numberOfPosition, float * positions ) {
    VertexBuffer * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    staticVertexies_.push_back( VertexBufferPtr( vbo ) );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_dynamic( size_t numberOfPosition, float * positions ) {
    VertexBuffer * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    dynamicVertexies_.push_back( VertexBufferPtr( vbo ) );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_stream( size_t numberOfPosition, float * positions ) {
    VertexBuffer * const vbo = new VertexBufferDX9Imp( numberOfPosition, positions );
    streamVertexies_.push_back( VertexBufferPtr( vbo ) );
    return vbo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_static( size_t numberOfIndex, unsigned short * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    staticIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_dynamic( size_t numberOfIndex, unsigned short * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    dynamicIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_stream( size_t numberOfIndex, unsigned short * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    streamIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_static( size_t numberOfIndex, unsigned int * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    staticIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_dynamic( size_t numberOfIndex, unsigned int * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    dynamicIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_stream( size_t numberOfIndex, unsigned int * indexies ) {
    IndexBuffer * const ibo = new IndexBufferDX9Imp( numberOfIndex, indexies );
    streamIndexies_.push_back( IndexBufferPtr( ibo ) );
    return ibo;
}

Surface * RenderBufferFactoryDX9Imp::getBackBuffer( size_t whichBackBuffer ) {
    IDirect3DSurface9 * newDXSurface;
    const HRESULT hr = getD3D9()->GetBackBuffer( 0, whichBackBuffer, D3DBACKBUFFER_TYPE_MONO, &newDXSurface );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"RenderWin32DX9Imp::getBackBuffer", hr );
        return NULL;
    }

    SurfaceDX9Imp * const newSurface = new SurfaceDX9Imp( newDXSurface );
    surfaces_.push_back( SurfaceDX9ImpPtr( newSurface ) );  
    return newSurface;
}

bool RenderBufferFactoryDX9Imp::releaseSurface( Surface * surface ) {
    MY_FOR_EACH( Surfaces, iter, surfaces_ ) {
        if( surface != &**iter ) continue;
        surfaces_.erase( iter );
        return true;
    }
    return false;
}

void RenderBufferFactoryDX9Imp::init( RenderBufferFactory * )
{

}

void RenderBufferFactoryDX9Imp::displayReset( RenderBufferFactory *, int x, int y, int width, int height )
{

}

void RenderBufferFactoryDX9Imp::displayLost( RenderBufferFactory * )
{

}

void RenderBufferFactoryDX9Imp::destroy( RenderBufferFactory * )
{

}

IDirect3DDevice9 * RenderBufferFactoryDX9Imp::getD3D9() {
    return d3dDevice_;
}


}
