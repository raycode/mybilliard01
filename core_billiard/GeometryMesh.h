#pragma once
namespace my_render {


INTERFACE_ GeometryMesh {
public:
    virtual void draw( Render * render ) = 0;

    virtual size_t getNumVertex() = 0;

public: virtual ~GeometryMesh() {}
};


}
