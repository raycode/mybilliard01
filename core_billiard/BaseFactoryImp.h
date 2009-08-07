#pragma once
namespace my_render_imp {

class BaseFactoryImp : IMPLEMENTS_ BaseFactory {
public:
    virtual Node * createVisualScene( domVisual_sceneRef );
    virtual Geometry * createGeometry( domGeometryRef );

    virtual void release( Base * );

private:
    typedef list< BasePtr > CreatedObjects;
    CreatedObjects createdObjects_;
};

}