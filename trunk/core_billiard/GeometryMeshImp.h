#pragma once
namespace my_render_imp {


class GeometryMeshImp : IMPLEMENTS_( GeometryMesh ) {
public: // from GeometryMesh
    virtual void draw( Render * render );
    virtual size_t getNumVertex();

public: // set
    void setPositions( const vector< NxReal > & stream );
    void setNormals( const vector< NxReal > & stream );
    void setTexCoords( const vector< NxReal > & stream );

public: // primitive
    void appendPrimitive( GeometryMeshPrimitiveImp * primitive );
    size_t getNumPrimitives();
    GeometryMeshPrimitiveImp * getPrimitive( size_t index );

private:
    typedef vector< NxVec3 > Vec3s;
    Vec3s positions_;

    typedef vector< GeometryMeshPrimitiveImp * > Primitives;
    Primitives primitives_;
};


}
