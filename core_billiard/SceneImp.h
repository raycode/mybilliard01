#pragma once
namespace my_render_imp {


class SceneImp : IMPLEMENTS_( Scene ) {
public: // from Scene
    virtual bool load( wstring filename, Factory * factory ) OVERRIDE;

    virtual void setRender( Render * render ) OVERRIDE;
    virtual Render * getRender()  OVERRIDE{ return render_; }

    virtual void update() OVERRIDE;
    virtual void render() OVERRIDE;

    virtual vector< wstring > getVisualSceneIDs() OVERRIDE;
    virtual wstring getDefaultVisualSceneID() OVERRIDE;

    virtual wstring getCurrentVisualSceneID() OVERRIDE;
    virtual bool setCurrentVisualScene( wstring sceneID ) OVERRIDE;

public:
    SceneImp();

private: // initRender
    bool initRender();
    static void initRenderUpAxis( Render * render, domCOLLADA * collada );

private: // load
    void loadLibraryImagesArray();
    void loadLibraryEffectsArray();
    void loadLibraryMaterialsArray();
    void loadLibraryAnimationsArray();
    void loadLibraryGeometriesArray();
    void loadLibraryVisualScenesArray();
    void loadLibraryScene();

    void addDefaultLight();
    void addDefaultCamera();

private: // retrieve data
    daeElement * idLookup( wstring id );
    Node * getNode( wstring nodeID );

    Geometry * getGeometryByID( wstring id );
    Geometry * getGeometryByName( wstring name );

private: // update
    float updateTimeDelta();
    void updateTransformWithPhysics( float timeDelta );
    void updateCamera( float timeDelta );
    void updateSceneGraph( float timeDelta );

private: // load
    static wstring getFilenameOnly( wstring fullFilename );
    static wstring getPathnameOnly( wstring fullFilename );
    wstring filename_, pathname_;

private:
    Render * render_;
    DAEPtr dae_;
    domCOLLADA * collada_;
    Factory * factory_;

private: // runtime database
    typedef vector< Geometry * > Geometries;
    typedef map< wstring, Node * > VisualScenes;
    typedef map< wstring, Node * > Nodes;

    Geometries geometries_;
    VisualScenes visualScenes_;
    Nodes nodes_;

private:
    Node * currentScene_;
    Camera * currentCamera_;

private: // I cannot came up with better names
    void appendNodes( Node * node );

};


}