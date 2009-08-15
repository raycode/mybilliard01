#pragma once
namespace my_render {


INTERFACE_ Instance {
public:
    virtual Base * getInstanceOwner() = 0;
    virtual wstring getUrl() = 0;
    virtual Base * getResolvedReferrence() = 0;

public: virtual ~Instance() {}
};

}
