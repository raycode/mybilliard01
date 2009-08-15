#pragma once
namespace my_render {


INTERFACE_ VertexBuffer {
public:
    virtual bool appendTexCoord1D_Array( const float * texCoords_1floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendTexCoord2D_Array( const float * texCoords_2floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendTexCoord3D_Array( const float * texCoords_3floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendTexCoord4D_Array( const float * texCoords_4floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendNormal_Array( const float * normals_3floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendBinormal_Array( const float * binormal_3floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendTangent_Array( const float * tangent_3floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendUV_Array( const float * ut_2floatsForEach, size_t usageIndex ) = 0;
    virtual bool appendColor_Array( const NxU32 * color_3UnsignedIntForEach, size_t usageIndex ) = 0;

    virtual size_t getNumberOfVertex() = 0;

public: virtual ~VertexBuffer() {}
};


}
