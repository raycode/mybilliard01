#pragma once
namespace my_render {


INTERFACE_ ShaderVariable {
public:
    virtual const wchar_t * getVariableName() = 0;

public: virtual ~ShaderVariable() {}
};


}