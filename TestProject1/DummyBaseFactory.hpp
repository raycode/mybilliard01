#pragma once

class DummyBaseFactory : IMPLEMENTS_ Factory {
public:
    virtual Node * createVisualScene( domVisual_sceneRef ) { return NULL; }
    virtual Geometry * createGeometry( domGeometryRef ) { return NULL; }

    virtual void release( Base * ) {}
};