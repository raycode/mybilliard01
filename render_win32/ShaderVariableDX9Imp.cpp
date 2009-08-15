#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


wstring ShaderVariableDX9Imp::getVariableName()
{
    return name_;
}

D3DXHANDLE ShaderVariableDX9Imp::getHandleDX9()
{
    return handle_;
}

ShaderVariableDX9Imp::ShaderVariableDX9Imp( wstring name, D3DXHANDLE handle )
{
    name_ = name;
    handle_ = handle;
}


}