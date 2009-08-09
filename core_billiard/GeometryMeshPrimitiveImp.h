#pragma once
namespace my_render_imp {


class GeometryMeshPrimitiveImp : IMPLEMENTS_( GeometryMeshPrimitive ) {
public: // from GeometryMeshPrimitive
    virtual wstring getName();
    virtual size_t getTriangleCount();
    virtual wstring getMaterialName();

    virtual void draw( Render * render );

public:
    GeometryMeshPrimitiveImp();

public: // set
    void setName( wstring name );
    void setTriangleCount( size_t nTriangle );
    void setMaterialName( wstring materialName );

private: // from GeometryMeshPrimitive
    wstring name_, materialName_;
    size_t numTriangles_;

private: // index
    Indexies positionIndex_;

private: // normal
    typedef vector< NxVec3 > Normals;
    Normals normals_;

private: // texture
    struct Tex2D {
        NxReal u, v;
    };
    typedef vector< Tex2D > Tex2Ds;
    typedef list< Tex2Ds > MultiTex2Ds;
    MultiTex2Ds multiTex2Ds_;

private: // for rendering
    Render::EPrimitiveType primitiveType_;
    Render::VertexBufferID vertexBuffer_;
    Render::IndexBufferID indexBuffer_;
};


}
