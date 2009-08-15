#pragma once
namespace my_render {


INTERFACE_ Base {
public:
    virtual const wchar_t * getID() = 0;
    virtual const wchar_t * getName() = 0;
    virtual const wchar_t * getURI() = 0;

public: virtual ~Base() {}
};


}