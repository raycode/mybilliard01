#pragma once
namespace my_render {


MY_INTERFACE Base {
    virtual ~Base() {}

    virtual wstring getID() PURE;
    virtual wstring getName() PURE;
    virtual wstring getURI() PURE;

};


}