#pragma once
namespace my_render {

INTERFACE_ InstanceResolver {
public:
    virtual Base * resolveInstanceUrl( wstring id ) = 0;

    virtual Instance * createInstance( wstring url, Base * owner ) = 0;
    virtual void releaseInstance( Instance * ) = 0;

public: virtual ~InstanceResolver() {}
};

}
