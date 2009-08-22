#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE ShaderVariableHandleDX9 {
    virtual ~ShaderVariableHandleDX9() {}

    virtual D3DXHANDLE getHandleDX9() PURE;

};

}
