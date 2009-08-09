#pragma once
namespace my_render_imp {


class GeometryMeshInput {
public:
    GeometryMeshInput( domInputLocalOffset_Array inputs );

    void setIndexies( domListOfUInts );

    bool hasNext();
    void getNext();

    bool hasNormal();
    bool hasBinormal();
    bool hasTangent();
    bool hasColor();

    NxVec3 getVertex();
    NxVec3 getNormal();
    NxVec3 getBinormal();
    NxVec3 getTangent();
    NxVec3 getColor();

    size_t getNumTexture();
    GeometryMeshPrimitiveImp::Tex2D getTexCoord( size_t index );

private:
    domSource * getSource( domInputLocalOffsetRef input );
    size_t getMaxOffset();
    size_t getCurrentIndex( size_t offset );

    domInputLocalOffset_Array inputs_;
    domListOfUInts indexies_;
    size_t currentPosition_;

    int position_offset_;
    int normal_offset_;
    int binormal_offset_;
    int tangent_offset_;
    int color_offset_;
    vector< int > texture_offset_Array_;

    domListOfFloats * positions_;
    domListOfFloats * normals_;
    domListOfFloats * binormals_;
    domListOfFloats * tangents_;
    domListOfFloats * colors_;
    vector< domListOfFloats * > textures_Array_;
};


}
