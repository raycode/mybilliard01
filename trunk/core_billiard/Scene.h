#pragma once
namespace my_render {


MY_INTERFACE Scene {
    virtual ~Scene() {}

    virtual void setColladaFactoryBeforeLoad( ColladaFactory * factory ) PURE;
    virtual void setRenderFactory( RenderBufferFactory * renderFactory ) PURE;

    virtual bool load( wstring filename ) PURE;
    virtual void unload() PURE;

    virtual size_t getNumberOfVisualScene() PURE;
    virtual Node * getVisualSceneByIndex( size_t index ) PURE;
    virtual Node * getVisualSceneByID( wstring id ) PURE;
    virtual Node * getDefaultVisualScene() PURE;
    virtual Node * getCurrentVisualScene() PURE;
    virtual bool setCurrentVisualScene( Node * ) PURE;

    virtual size_t getNumberOfNode() PURE;
    virtual Node * getNodeByIndex( size_t index ) PURE;
    virtual Node * getNodeByID( wstring nodeID ) PURE;

    virtual size_t getNumberOfGeometry() PURE;
    virtual Geometry * getGeometryByIndex( size_t index ) PURE;
    virtual Geometry * getGeometryByID( wstring id ) PURE;
    virtual Geometry * getGeometryByName( wstring name ) PURE;

    virtual size_t getNumberOfCamera() PURE;
    virtual Camera * getCameraByIndex( size_t index ) PURE;
    virtual Camera * getCameraByID( wstring id ) PURE;
    virtual Camera * getCameraByName( wstring name ) PURE;

    virtual bool isUpAxisX() PURE;
    virtual bool isUpAxisY() PURE;
    virtual bool isUpAxisZ() PURE;
};

}