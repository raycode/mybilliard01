#pragma once
namespace my_render {


INTERFACE_ ShaderVariable {
public:
    virtual wstring getVariableName() = 0;

public: virtual ~ShaderVariable() {}
};


}