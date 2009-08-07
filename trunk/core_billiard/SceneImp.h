#pragma once
namespace my_render_imp {


class SceneImp : IMPLEMENTS_ Scene {
public: // from Scene
    void update();
    void render( RenderImp * render );

public:
    SceneImp( RenderImp * render );
    bool load( wstring filename );

private: // load
    void loadUpAxis();
    void loadLibraryImagesArray();
    void loadLibraryEffectsArray();
    void loadLibraryMaterialsArray();
    void loadLibraryAnimationsArray();
    void loadInstanceVisualScene();

    void addDefaultLight();
    void addDefaultCamera();

private:
    RenderImp * const render_;

    DAEPtr dae_;
    domCOLLADA * collada_;
    NodeImp * sceneRoot_;
};


}