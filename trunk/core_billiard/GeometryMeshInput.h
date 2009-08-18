#pragma once
namespace my_render_imp {


class GeometryMeshInput {
public:
    GeometryMeshInput( domInputLocalOffset_Array inputs );
    void setNewIndices( const domListOfUInts & );

    bool hasVertex();
    void moveToNextVertex();

    size_t getNumberOfNormalSet();
    size_t getNumberOfBiNormalSet();
    size_t getNumberOfTangentSet();
    size_t getNumberOfColorSet();
    size_t getNumberOfTexCoord2DSet();

    NxVec3 getVertex();
    NxVec3 getNormal( size_t whichSet );
    NxVec3 getBinormal( size_t whichSet );
    NxVec3 getTangent( size_t whichSet );
    NxVec3 getColor( size_t whichSet );
    NxReal getTexCoord2D_U( size_t whichSet );
    NxReal getTexCoord2D_V( size_t whichSet );

private:
    enum ESEMANTIC_TYPE { ETYPE_POSITION, ETYPE_NORMAL, ETYPE_BINORMAL, ETYPE_TANGENT, ETYPE_COLOR, ETYPE_TEXCOORD, SIZE_OF_ETYPE };

    void storeEachSemantic( ESEMANTIC_TYPE semanticType, size_t offset, size_t set, const domListOfFloats & data );

    size_t getCurrentIndex( ESEMANTIC_TYPE semanticType, size_t whichSet );
    domFloat * getCurrentSource( ESEMANTIC_TYPE semanticType, size_t whichSet, size_t numberOfUnit );

private:
    domSource * getSourceFromInput( domInputLocalOffsetRef input );
    size_t getStepOfOffset();

private:
    domListOfUInts indices;
    size_t currentPosition_;

private:
    typedef vector< int > Offset_Array;
    Offset_Array offset_array_[ SIZE_OF_ETYPE ];

    typedef vector< domListOfFloats > Floats_Array;
    Floats_Array source_array_[ SIZE_OF_ETYPE ];

};


}
