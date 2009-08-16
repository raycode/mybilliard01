#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ShaderVariableDX9 : EXTENDS_INTERFACE_STATIC_( ShaderVariable ) {

    virtual D3DXHANDLE getHandleDX9() = 0;
};


}