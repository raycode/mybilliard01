#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ RenderWin32DX9 : EXTENDS_INTERFACE_( RenderWin32 ) {
public:
    virtual IDirect3DDevice9 * getD3D9() = 0;
};


}