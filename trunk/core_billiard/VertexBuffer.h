#pragma once
namespace my_render {


INTERFACE_ VertexBuffer {
public:
    virtual void appendRHW_Array( const float * rhw_onlyW ) = 0;
    virtual void appendBlendingWeight_Array( const float * blendingWeights ) = 0;
    virtual void appendNormal_Array( const float * normals_3floatsForEach ) = 0;
    virtual void appendPixelSize_Array( const float * pixelSizes ) = 0;
    virtual void appendDiffuse_Array( const NxU32 * colors_3UnsignedIntForEach ) = 0;
    virtual void appendSpecular_Array( const NxU32 * colors_3UnsignedIntForEach ) = 0;
    virtual void appendTexCoord2D_Array( const float * texCoords_2floatsForEach ) = 0;

    virtual size_t getNumberOfVertex() = 0;
    virtual bool hasRHW() = 0;
    virtual size_t getNumberOfBlendingWeights() = 0;
    virtual bool hasNormal() = 0;
    virtual bool hasPixelSize() = 0;
    virtual bool hasDiffuse() = 0;
    virtual bool hasSpecular() = 0;
    virtual size_t getNumberOfTexCoords() = 0;

public: virtual ~VertexBuffer() {}
};


}
