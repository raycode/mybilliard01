#pragma once
namespace my_render_imp {


class GeometryImp : public BaseImp, IMPLEMENTS_( Geometry ) {
public:
    virtual void draw( Render * render );

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