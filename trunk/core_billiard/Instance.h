#pragma once
namespace my_render {


MY_INTERFACE Instance {
    virtual ~Instance() {}

    virtual Base * getInstanceOwner() = 0;
    virtual wstring getUrl() = 0;
    virtual Base * getResolvedReferrence() = 0;

};

}
