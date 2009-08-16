#pragma once
namespace my_render {


MY_INTERFACE ShaderVariableWriter {
    virtual ~ShaderVariableWriter() {}

    virtual void setBool( ShaderVariable * variable, bool ) = 0;
    virtual void setBoolArray( ShaderVariable * variable, const bool *, size_t siz ) = 0;

    virtual void setFloat( ShaderVariable * variable, float ) = 0;
    virtual void setFloatArray( ShaderVariable * variable, const float *, size_t siz ) = 0;

    virtual void setInt( ShaderVariable * variable, int ) = 0;
    virtual void setIntArray( ShaderVariable * variable, const int *, size_t siz ) = 0;

};


}