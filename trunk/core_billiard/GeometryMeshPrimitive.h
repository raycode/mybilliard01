#pragma once
namespace my_render {


INTERFACE_ GeometryMeshPrimitive {
public:
    virtual const wchar_t * getName() = 0;
    virtual size_t getTriangleCount() = 0;
    virtual const wchar_t * getMaterialName() = 0;

    virtual void draw( Render * render ) = 0;

public:
    typedef unsigned int VertexIndex;

public: virtual ~GeometryMeshPrimitive() {}
};


}
