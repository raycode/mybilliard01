#pragma once
namespace my_render {


INTERFACE_ VertexBuffer {
public:
    virtual void appendNormal( float * normals ) = 0;
    virtual void appendTexCoord( float * texCoords ) = 0;

    virtual size_t getNumberOfVertex() = 0;
    virtual bool hasNormal() = 0;
    virtual size_t getNumberOfTexCoords() = 0;

public: virtual ~VertexBuffer() {}
};


}
