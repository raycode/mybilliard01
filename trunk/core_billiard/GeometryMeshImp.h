#pragma once
namespace my_render_imp {


class GeometryMeshImp : IMPLEMENTS_( GeometryMesh ) {
public: // from GeometryMesh
    virtual void draw( Render * render );

public: // primitive
    void appendPrimitive( GeometryMeshPrimitiveImp * primitive );
    size_t getNumPrimitives();
    GeometryMeshPrimitiveImp * getPrimitive( size_t index );

private:
    typedef vector< GeometryMeshPrimitiveImp * > Primitives;
    Primitives primitives_;
};


}
