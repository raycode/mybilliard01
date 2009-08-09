#pragma once
namespace my_render {


INTERFACE_ GeometryMeshPrimitive {
public:
    virtual wstring getName() = 0;
    virtual size_t getTriangleCount() = 0;
    virtual wstring getMaterialName() = 0;

    virtual void draw( Render * render ) = 0;

public:
    typedef unsigned int VertexIndex;

public: virtual ~GeometryMeshPrimitive() {}
};


}
