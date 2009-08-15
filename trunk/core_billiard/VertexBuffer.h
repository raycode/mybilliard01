#pragma once
namespace my_render {


INTERFACE_ VertexBuffer {
public:
    virtual void appendTexCoord1D_Array( const float * texCoords_1floatsForEach, size_t usageIndex ) = 0;
    virtual void appendTexCoord2D_Array( const float * texCoords_2floatsForEach, size_t usageIndex ) = 0;
    virtual void appendTexCoord3D_Array( const float * texCoords_3floatsForEach, size_t usageIndex ) = 0;
    virtual void appendTexCoord4D_Array( const float * texCoords_4floatsForEach, size_t usageIndex ) = 0;
    virtual void appendNormal_Array( const float * normals_3floatsForEach, size_t usageIndex ) = 0;
    virtual void appendBinormal_Array( const float * binormal_3floatsForEach, size_t usageIndex ) = 0;
    virtual void appendTangent_Array( const float * tangent_3floatsForEach, size_t usageIndex ) = 0;
    virtual void appendUV_Array( const float * ut_2floatsForEach, size_t usageIndex ) = 0;
    virtual void appendColor_Array( const float * color_3floatsForEach, size_t usageIndex ) = 0;

    virtual size_t getNumberOfVertex() = 0;

public: virtual ~VertexBuffer() {}
};


}
