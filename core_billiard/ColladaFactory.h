#pragma once
namespace my_render {


MY_INTERFACE ColladaFactory {
    virtual ~ColladaFactory() {}

    virtual Node * createVisualScene( domVisual_sceneRef ) PURE;
    virtual Geometry * createGeometry( domGeometryRef ) PURE;

    virtual bool destroy( Base * ) PURE;

};

}