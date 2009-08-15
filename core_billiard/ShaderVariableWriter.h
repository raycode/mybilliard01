#pragma once
namespace my_render {


INTERFACE_ ShaderVariableWriter {
public:
    virtual void setBool( wstring variable, bool ) = 0;
    virtual void setBoolArray( wstring variable, const bool *, size_t siz ) = 0;

    virtual void setFloat( wstring variable, float ) = 0;
    virtual void setFloatArray( wstring variable, const float *, size_t siz ) = 0;

    virtual void setInt( wstring variable, int ) = 0;
    virtual void setIntArray( wstring variable, const int *, size_t siz ) = 0;

public: virtual ~ShaderVariableWriter() {}
};


}