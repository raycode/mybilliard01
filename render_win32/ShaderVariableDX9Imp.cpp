#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


const wchar_t * ShaderVariableDX9Imp::getVariableName()
{
    return name_.c_str();
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