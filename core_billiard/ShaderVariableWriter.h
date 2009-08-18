#pragma once
namespace my_render {


MY_INTERFACE ShaderVariableWriter {
    virtual ~ShaderVariableWriter() {}

    virtual void setBool( ShaderVariable * variable, bool ) PURE;
    virtual void setBoolArray( ShaderVariable * variable, const bool *, size_t siz ) PURE;

    virtual void setFloat( ShaderVariable * variable, float ) PURE;
    virtual void setFloatArray( ShaderVariable * variable, const float *, size_t siz ) PURE;

    virtual void setInt( ShaderVariable * variable, int ) PURE;
    virtual void setIntArray( ShaderVariable * variable, const int *, size_t siz ) PURE;

};


}