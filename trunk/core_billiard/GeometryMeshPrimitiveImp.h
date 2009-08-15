#pragma once
namespace my_render_imp {


class GeometryMeshPrimitiveImp : IMPLEMENTS_( GeometryMeshPrimitive ) {
public: // from GeometryMeshPrimitive
    virtual wstring getName() OVERRIDE;
    virtual size_t getTriangleCount() OVERRIDE;
    virtual wstring getMaterialName() OVERRIDE;

    virtual void draw( Render * render );

public:
    GeometryMeshPrimitiveImp();

    void updateVertexIndexBuffers( Render * render );

    size_t getNumVertex();

public: // set
    void setName( wstring name );
    void setTriangleCount( size_t nTriangle );
    void setMaterialName( wstring materialName );
    void setRenderingPrimitiveType( int primitiveTypeID );

public: // set
    void appendPosition( NxVec3 );
    void appendNormal( NxVec3 );
    void appendBinormal( NxVec3 );
    void appendTangent( NxVec3 );
    void appendColor( NxVec3 );
    void appendIndex( VertexIndex );

public: // set
    struct Tex2D {
        NxReal u, v;
    };
    void appendTexCoord( Tex2D, size_t index );

private: // from GeometryMeshPrimitive
    wstring name_, materialName_;
    size_t numTriangles_;

private: // position
    typedef vector< NxVec3 > Positions;
    Positions positions_;

private: // normal
    typedef vector< NxVec3 > Normals;
    Normals normals_;

private: // binormal
    typedef vector< NxVec3 > Binormals;
    Binormals binormals_;

private: // tangent
    typedef vector< NxVec3 > Tangents;
    Tangents tangents_;

private: // color
    typedef vector< NxVec3 > Colors;
    Colors colors_;

private: // texture
    typedef vector< Tex2D > Tex2Ds;
    typedef vector< Tex2Ds > MultiTex2Ds;
    MultiTex2Ds multiTex2Ds_;

private: // index
    typedef vector< VertexIndex > VertexIndex_Array;
    VertexIndex_Array vertexIndex_Array_;

private: // for rendering
    int primitiveTypeID_;
    VertexBuffer * vertexBuffer_;
    IndexBuffer * indexBuffer_;
};


}
