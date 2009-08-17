#pragma once
namespace my_render_imp {


class GeometryImp : public BaseImp, IMPLEMENTS_INTERFACE( Geometry ) {
public:
    virtual void draw( Render * render ) OVERRIDE;

public:
    GeometryImp();

public: // set
    void setMesh( GeometryMesh * newMesh );
    void setConvexMesh() {}
    void setSpline() {}

public: // get
    GeometryMesh * getMesh();
    void getConvexMesh() {}
    void getSpline() {}

private:
    GeometryMesh * mesh_;
};


}