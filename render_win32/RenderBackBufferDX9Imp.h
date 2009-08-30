#pragma once
namespace my_render_win32_dx9_imp {


class RenderBackBufferDX9Imp : IMPLEMENTS_INTERFACE( RenderBackBufferDX9 ) {
public:
    RenderBackBufferDX9Imp( size_t whichBackBuffer );
};

}
