#pragma once
namespace my_render_imp {


class GeometryImp : public BaseImp, IMPLEMENTS_INTERFACE( Geometry ) {
public:
    virtual void display() OVERRIDE;
    virtual void display_positionOnly() OVERRIDE;

    virtual GeometryMesh * getMesh() OVERRIDE;
    virtual GeometryMesh * getMesh_positionOnly() OVERRIDE;

public:
    GeometryImp();

private:
    GeometryMeshPtr mesh_, mesh_positionOnly_;
};


}