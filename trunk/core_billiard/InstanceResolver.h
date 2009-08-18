#pragma once
namespace my_render {


MY_INTERFACE InstanceResolver {
    virtual ~InstanceResolver() {}

    virtual Instance * createInstance( wstring url, Base * owner ) PURE;
    virtual bool destroyInstance( Instance * ) PURE;

    virtual Base * resolveInstanceUrl( wstring id ) PURE;

};

}
