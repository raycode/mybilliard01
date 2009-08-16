#pragma once
namespace my_render {


MY_INTERFACE Factory {
    virtual ~Factory() {}

    virtual Node * createVisualScene( domVisual_sceneRef ) = 0;
    virtual Geometry * createGeometry( domGeometryRef ) = 0;

    virtual void release( Base * ) = 0;

};

}