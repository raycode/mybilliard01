#pragma once
namespace my_render_imp {


class GeometryMeshPrimitiveImp : IMPLEMENTS_INTERFACE( GeometryMeshPrimitive )
{
public: // from GeometryMeshPrimitive
    virtual wstring getName() OVERRIDE;
    virtual size_t getTriangleCount() OVERRIDE;
    virtual wstring getMaterialName() OVERRIDE;

    virtual void buildDeviceBuffer_onStatic( RenderBufferFactory * ) OVERRIDE;
    virtual void buildDeviceBuffer_onDynamic( RenderBufferFactory * ) OVERRIDE;
    virtual void buildDeviceBuffer_onStream( RenderBufferFactory * ) OVERRIDE;

public: // from GeometryDisplayable
    virtual void display() OVERRIDE;
    virtual void display_positionOnly() OVERRIDE;

public:
    GeometryMeshPrimitiveImp();

    size_t getNumberOfVertex();

public: // set
    void setName( wstring name );
    void setTriangleCount( size_t nTriangle );
    void setMaterialName( wstring materialName );
    void setRenderingPrimitiveType( int primitiveTypeID );

public: // append vertex information
    void appendPosition( NxVec3 );
    void appendNormal( NxVec3, size_t whichSet );
    void appendBinormal( NxVec3, size_t whichSet );
    void appendTangent( NxVec3, size_t whichSet );
    void appendColor( NxVec3, size_t whichSet );
    void appendTexCoord2D( NxReal u, NxReal v, size_t whichSet );

private: // display by draw type
    typedef void (VertexBuffer::DrawPrimitive::*Draw_pointer)();
    Draw_pointer display_pointer_;

private: // build buffers on device
    void buildDeviceBuffer( VertexBuffer * vertexBuffer );

private: // from GeometryMeshPrimitive
    wstring name_, materialName_;
    size_t numTriangles_;

private:
    enum ESEMANTIC_TYPE { ETYPE_POSITION, ETYPE_NORMAL, ETYPE_BINORMAL, ETYPE_TANGENT, ETYPE_COLOR, ETYPE_TEXCOORD_2D, SIZE_OF_ETYPE };

    typedef vector< NxVec3 > Semantic;
    typedef vector< Semantic > SemanticSet;
    SemanticSet semanticSet_[ SIZE_OF_ETYPE ];

private: // for rendering
    int primitiveTypeID_;
    VertexBuffer * vertexBuffer_;
};


}
