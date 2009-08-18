#pragma once
namespace my_render {


MY_INTERFACE GeometryMeshPrimitive {
    virtual ~GeometryMeshPrimitive() {}

    virtual wstring getName() PURE;
    virtual size_t getTriangleCount() PURE;
    virtual wstring getMaterialName() PURE;

    virtual void display( Render * render ) PURE;

    virtual void buildDeviceBuffer( RenderBufferFactory * ) PURE;
};


}
