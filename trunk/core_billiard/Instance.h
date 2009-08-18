#pragma once
namespace my_render {


MY_INTERFACE Instance {
    virtual ~Instance() {}

    virtual Base * getInstanceOwner() PURE;
    virtual wstring getUrl() PURE;
    virtual Base * getResolvedReferrence() PURE;

};

}
