#pragma once
namespace my_render {


INTERFACE_ Base {
public:
    virtual wstring getID() = 0;
    virtual wstring getName() = 0;
    virtual wstring getURI() = 0;

public: virtual ~Base() {}
};


}