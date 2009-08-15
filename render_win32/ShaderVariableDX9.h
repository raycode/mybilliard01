#pragma once
namespace my_render_win32_dx9 {


INTERFACE_ ShaderVariableDX9 : EXTENDS_INTERFACE_STATIC_( ShaderVariable )
{
public:
    virtual D3DXHANDLE getHandleDX9() = 0;
};


}