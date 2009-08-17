#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ShaderVariableDX9 : STATIC_EXTENDS_INTERFACE( ShaderVariable ), EXTENDS_INTERFACE( ReleasableResourceDX9 ) {

    virtual D3DXHANDLE getHandleDX9() = 0;
};


}