#pragma once
namespace my_render {


MY_INTERFACE VertexBuffer {
    virtual ~VertexBuffer() {}

    virtual bool appendTexCoord1D_Array( const float * texCoords_1floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendTexCoord2D_Array( const float * texCoords_2floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendTexCoord3D_Array( const float * texCoords_3floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendTexCoord4D_Array( const float * texCoords_4floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendNormal_Array( const float * normals_3floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendBinormal_Array( const float * binormal_3floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendTangent_Array( const float * tangent_3floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendUV_Array( const float * ut_2floatsForEach, size_t usageIndex ) PURE;
    virtual bool appendColor_Array( const NxU32 * color_3UnsignedIntForEach, size_t usageIndex ) PURE;

    virtual size_t getNumberOfVertex() PURE;

};


}
