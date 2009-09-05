#pragma once
namespace my_render_imp {


class GeometryImp
    : public BaseImp
    , IMPLEMENTS_INTERFACE( Geometry )
{
public: // from Geometry
    virtual GeometryMesh * getMesh() OVERRIDE;

public: // Displayable
    virtual void display() OVERRIDE;
    virtual void display_positionOnly() OVERRIDE;

public:
    GeometryImp();

private:
    GeometryMeshImpPtr mesh_;
};


}