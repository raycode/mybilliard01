#pragma once
namespace my_render_win32_dx9_imp {


class ShaderVariableDX9Imp : IMPLEMENTS_( ShaderVariableDX9 ) {
public: // from ShaderVariable
    virtual const wchar_t * getVariableName() OVERRIDE;

public: // from ShaderVariableDX9
    virtual D3DXHANDLE getHandleDX9() OVERRIDE;

public:
    ShaderVariableDX9Imp( wstring name, D3DXHANDLE handle );

private:
    wstring name_;
    D3DXHANDLE handle_;
};


}