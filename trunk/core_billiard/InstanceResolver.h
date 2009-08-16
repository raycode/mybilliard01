#pragma once
namespace my_render {


MY_INTERFACE InstanceResolver {
    virtual ~InstanceResolver() {}

    virtual Base * resolveInstanceUrl( wstring id ) = 0;

    virtual Instance * createInstance( wstring url, Base * owner ) = 0;
    virtual void releaseInstance( Instance * ) = 0;

};

}
