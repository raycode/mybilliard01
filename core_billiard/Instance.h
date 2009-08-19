#pragma once
namespace my_render {


MY_INTERFACE Instance {
    virtual ~Instance() {}

    virtual wstring getURL() PURE;
    virtual Base * getResolvedReference() PURE;

};

}
