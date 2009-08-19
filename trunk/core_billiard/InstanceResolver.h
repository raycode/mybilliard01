#pragma once
namespace my_render {


MY_INTERFACE InstanceResolver {
    virtual ~InstanceResolver() {}

    virtual Instance * createInstance( wstring url ) PURE;
    virtual bool destroyInstance( Instance * ) PURE;

    virtual Base * resolveInstanceURL( wstring id ) PURE;

};

}
