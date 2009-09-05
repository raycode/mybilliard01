#pragma once
namespace my_render {


MY_INTERFACE GeometryMeshPrimitive : EXTENDS_INTERFACE( GeometryDisplayable ) {

    virtual wstring getName() PURE;
    virtual size_t getTriangleCount() PURE;
    virtual wstring getMaterialName() PURE;

    virtual void display() PURE;

    virtual void buildDeviceBuffer_onStatic( RenderBufferFactory * ) PURE;
    virtual void buildDeviceBuffer_onDynamic( RenderBufferFactory * ) PURE;
    virtual void buildDeviceBuffer_onStream( RenderBufferFactory * ) PURE;
};


}
