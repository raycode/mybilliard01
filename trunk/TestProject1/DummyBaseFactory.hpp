#pragma once

class DummyBaseFactory : IMPLEMENTS_INTERFACE( ColladaFactory ) {
public:
    virtual Node * createVisualScene( domVisual_sceneRef ) OVERRIDE { return NULL; }
    virtual Geometry * createGeometry( domGeometryRef ) OVERRIDE { return NULL; }

    virtual bool destroy( Base * ) OVERRIDE {}
};
