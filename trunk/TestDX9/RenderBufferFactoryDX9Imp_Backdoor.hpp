#pragma once

struct RenderBufferFactoryDX9Imp::TestingBackdoor {
};

struct VertexBufferDX9Imp::TestingBackdoor {
    PRIVATE_METHOD_0( size_t, VertexBufferDX9Imp, updateOffset );
    PRIVATE_MEMBER( vector< D3DVERTEXELEMENT9 >, VertexBufferDX9Imp, vertexElementDX9_ );
    PRIVATE_METHOD_0( size_t, VertexBufferDX9Imp, getSizeInByteForTotal );
    PRIVATE_METHOD_0( D3DVERTEXELEMENT9 *, VertexBufferDX9Imp, getVertexElement );
};


struct RenderWin32DX9Imp::TestingBackdoor {
    PRIVATE_METHOD_0( RenderBufferFactoryDX9 *, RenderWin32DX9Imp, getBufferFactory );
};

