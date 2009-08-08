#pragma once
namespace my_render_imp {


class SceneImp : IMPLEMENTS_ Scene {
public: // from Scene
    virtual bool load( wstring filename, Factory * factory );

    virtual void setRender( Render * render );
    virtual Render * getRender() { return render_; }

    virtual void update();
    virtual void render();

    virtual vector< wstring > getVisualSceneIDs();
    virtual wstring getDefaultVisualSceneID();

    virtual wstring getCurrentVisualSceneID();
    virtual bool setCurrentVisualScene( wstring sceneID );

    SceneImp();

private: // initRender
    bool initRender();
    static void initRenderUpAxis( Render * render, domCOLLADA * collada );

private: // load
    void loadLibraryImagesArray();
    void loadLibraryEffectsArray();
    void loadLibraryMaterialsArray();
    void loadLibraryAnimationsArray();
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
    Factory * baseFactory_;

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