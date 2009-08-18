#pragma once
namespace my_render {


MY_INTERFACE ShaderVariable {
    virtual ~ShaderVariable() {}
    
    virtual wstring getVariableName() PURE;

};


}