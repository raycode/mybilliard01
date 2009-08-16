#pragma once
namespace my_render {


MY_INTERFACE Base {
    virtual ~Base() {}

    virtual wstring getID() = 0;
    virtual wstring getName() = 0;
    virtual wstring getURI() = 0;

};


}