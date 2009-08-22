#pragma once
namespace my_render_imp {


class GeometryImp : public BaseImp, IMPLEMENTS_INTERFACE( Geometry ) {
public:
    virtual void display() OVERRIDE;

    virtual GeometryMesh * getMesh() OVERRIDE;

public:
    GeometryImp();

private:
    GeometryMeshPtr mesh_;
};


}