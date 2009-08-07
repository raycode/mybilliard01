#pragma once
namespace my_render {

INTERFACE_ BaseFactory {
public:
    virtual Node * createVisualScene( domVisual_sceneRef ) = 0;
    virtual Geometry * createGeometry( domGeometryRef ) = 0;

    virtual void release( Base * ) = 0;

public: virtual ~BaseFactory() {}
};

}