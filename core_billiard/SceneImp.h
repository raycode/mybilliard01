#pragma once
namespace my_render_imp {


class SceneImp : IMPLEMENTS_INTERFACE( Scene ) {
public: // from Scene
    virtual void setColladaFactoryBeforeLoad( ColladaFactory * factory ) OVERRIDE;
    virtual void setRenderFactory( RenderBufferFactory * renderFactory ) OVERRIDE;

    virtual bool load( wstring filename ) OVERRIDE;
    virtual void unload() OVERRIDE;

    virtual size_t getNumberOfVisualScene() OVERRIDE;
    virtual Node * getVisualSceneByIndex( size_t index ) OVERRIDE;
    virtual Node * getVisualSceneByID( wstring id ) OVERRIDE;
    virtual Node * getDefaultVisualScene() OVERRIDE;
    virtual Node * getCurrentVisualScene() OVERRIDE;
    virtual bool setCurrentVisualScene( Node * ) OVERRIDE;

    virtual size_t getNumberOfNode() OVERRIDE;
    virtual Node * getNodeByIndex( size_t index ) OVERRIDE;
    virtual Node * getNodeByID( wstring nodeID ) OVERRIDE;

    virtual size_t getNumberOfGeometry() OVERRIDE;
    virtual Geometry * getGeometryByIndex( size_t index ) OVERRIDE;
    virtual Geometry * getGeometryByID( wstring id ) OVERRIDE;
    virtual Geometry * getGeometryByName( wstring name ) OVERRIDE;

    virtual size_t getNumberOfCamera() OVERRIDE;
    virtual Camera * getCameraByIndex( size_t index ) OVERRIDE;
    virtual Camera * getCameraByID( wstring id ) OVERRIDE;
    virtual Camera * getCameraByName( wstring name ) OVERRIDE;

    virtual bool isUpAxisX() OVERRIDE;
    virtual bool isUpAxisY() OVERRIDE;
    virtual bool isUpAxisZ() OVERRIDE;

public:
    SceneImp();
    ~SceneImp();

private: // load
    bool loadUpAxis( domCOLLADARef collada );
    void loadLibraryAnimations();
    void loadLibraryAnimationClips();
    void loadLibraryCameras();
    void loadLibraryControllers();
    void loadLibraryLights();
    void loadLibraryGeometries();
    void loadLibraryVisualScenes();
    void loadLibraryScene();

    void loadNodesFromVisualScene( Node * node );

private: // default
    void setDefaultsAfterLoad();
    void addDefaultCameraWhenThereIsNoCamera();

private: // update
    void updateDevice();
    void updateDevice_GeometryMesh( GeometryMesh * mesh );

    daeElementRef idLookup( wstring id );

private: // dae file
    void storeFilename( wstring filename );
    static wstring getFilenameOnly( wstring fullFilename );
    static wstring getPathnameOnly( wstring fullFilename );
    wstring filename_, pathname_;

private:
    ColladaFactory * colladaFactory_;
    RenderBufferFactory * renderFactory_;

    DAEPtr dae_;
    domCOLLADARef collada_;

    ColladaFactoryImp defaultFactory_;
    RenderBufferFactoryNull nullRenderFactory_;
    NodeNull nullNode_;

private: // runtime database
    typedef vector< Node * > VisualScenes;
    VisualScenes visualScenes_;

    typedef vector< Node * > Nodes;
    Nodes nodes_;

    typedef vector< Geometry * > Geometries;
    Geometries geometries_;

    typedef vector< Camera * > Cameras;
    Cameras cameras_;

    // effect

    // material

    // animation

    domUpAxisType upAxis_;

private:
    Node * currentScene_;
    Camera * currentCamera_;

    MY_UNIT_TEST_BACKDOOR;
};


}