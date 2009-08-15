#pragma once
namespace my_render {


INTERFACE_ Instance {
public:
    virtual Base * getInstanceOwner() = 0;
    virtual const wchar_t * getUrl() = 0;
    virtual Base * getResolvedReferrence() = 0;

public: virtual ~Instance() {}
};

}
