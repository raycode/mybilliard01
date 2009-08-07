#pragma once
namespace my_render {

INTERFACE_ Base {
public:
    virtual wstring getID() = 0;
    virtual wstring getSID() = 0;
    virtual wstring getName() = 0;

public: virtual ~Base() {}
};

}