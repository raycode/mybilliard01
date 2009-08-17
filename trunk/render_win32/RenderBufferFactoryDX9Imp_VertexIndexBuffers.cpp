#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_static( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( getD3D9Device(), numberOfPosition, positions, D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );
    pushBackToReadyQueue( E_STATIC_VERTICES, vbo );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_dynamic( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( getD3D9Device(), numberOfPosition, positions, D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );
    pushBackToReadyQueue( E_DYNAMIC_VERTICES, vbo );
    return vbo;
}

VertexBuffer * RenderBufferFactoryDX9Imp::createVertexBuffer_stream( size_t numberOfPosition, const float * positions ) {
    VertexBufferDX9 * const vbo = new VertexBufferDX9Imp( getD3D9Device(), numberOfPosition, positions, 0, D3DPOOL_SYSTEMMEM, 0 );
    pushBackToReadyQueue( E_STREAM_VERTICES, vbo );
    return vbo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_static( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( getD3D9Device(), numberOfIndex, indexies, D3DUSAGE_WRITEONLY, D3DPOOL_DEFAULT, 0 );
    pushBackToReadyQueue( E_STATIC_INDICES, ibo );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_dynamic( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( getD3D9Device(), numberOfIndex, indexies, D3DUSAGE_DYNAMIC, D3DPOOL_DEFAULT, 0 );
    pushBackToReadyQueue( E_DYNAMIC_INDICES, ibo );
    return ibo;
}

IndexBuffer * RenderBufferFactoryDX9Imp::createIndexBuffer_stream( size_t numberOfIndex, const unsigned int * indexies ) {
    IndexBufferDX9 * const ibo = new IndexBufferDX9Imp( getD3D9Device(), numberOfIndex, indexies, 0, D3DPOOL_SYSTEMMEM, 0 );
    pushBackToReadyQueue( E_STREAM_INDICES, ibo );
    return ibo;
}


}