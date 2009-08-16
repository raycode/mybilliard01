#pragma once
namespace my_render {


MY_INTERFACE GeometryMeshPrimitive {
    virtual ~GeometryMeshPrimitive() {}

    virtual wstring getName() = 0;
    virtual size_t getTriangleCount() = 0;
    virtual wstring getMaterialName() = 0;

    virtual void draw( Render * render ) = 0;

    typedef unsigned int VertexIndex;

};


}
