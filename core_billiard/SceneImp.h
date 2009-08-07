#pragma once
namespace my_render_imp {


class SceneImp : IMPLEMENTS_ Scene {
public: // from Scene
    virtual bool load( wstring filename );

    virtual void setRender( Render * render );
    virtual Render * getRender() { return render_; }

    virtual void update();
    virtual void render();

private: // load
    static wstring getFilenameOnly( wstring fullFilename );
    static wstring getPathnameOnly( wstring fullFilename );

    wstring filename_, pathname_;

private: // load
    void loadLibraryImagesArray();
    void loadLibraryEffectsArray();
    void loadLibraryMaterialsArray();
    void loadLibraryAnimationsArray();
    void loadInstanceVisualScene();

    void addDefaultLight();
    void addDefaultCamera();

private: // update
    float calculateTimeDelta();
    void updateTransformWithPhysics( float timeDelta );
    void updateCamera( float timeDelta );
    void updateSceneGraph( float timeDelta );

private: // setRender
    void setRenderUpAxis( Render * render );

private:
    DAEPtr dae_;
    domCOLLADA * collada_;
    NodeImp * sceneRoot_;

    Render * render_;
};


}