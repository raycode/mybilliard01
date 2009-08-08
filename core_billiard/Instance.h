#pragma once
namespace my_render {


INTERFACE_ Instance : public Base {
public:
    virtual Base * getInstanceOwner() = 0;
    virtual void setInstanceOwner( Base * owner ) = 0;

    virtual wstring getUrlID() = 0;
    virtual Base * getResolvedReferrence() = 0;

public: virtual ~Instance() {}
};

}
