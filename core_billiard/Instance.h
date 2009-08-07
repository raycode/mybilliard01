#pragma once
namespace my_render {


INTERFACE_ Instance {
public:
    virtual Node * getInstanceOwner() = 0;

public: virtual ~Instance() {}
};

}
