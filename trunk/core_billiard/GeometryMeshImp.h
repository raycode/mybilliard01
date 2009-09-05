#pragma once
namespace my_render_imp {


class GeometryMeshImp : IMPLEMENTS_INTERFACE( GeometryMesh )
{
public: // from GeometryMesh
    virtual void appendPrimitive( GeometryMeshPrimitive * primitive ) OVERRIDE;
    virtual size_t getNumberOfPrimitives() OVERRIDE;
    virtual GeometryMeshPrimitive * getPrimitive( size_t index ) OVERRIDE;

public: // from Displayable
    virtual void display() OVERRIDE;
    virtual void display_positionOnly() OVERRIDE;

private:
    typedef vector< GeometryMeshPrimitive * > Primitives;
    Primitives primitives_;
};


}
