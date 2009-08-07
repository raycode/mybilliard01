#pragma once
namespace my_render {

INTERFACE_ Scene {
public:
    virtual bool load( wstring filename, BaseFactory * factory ) = 0;

    virtual void setRender( Render * render ) = 0;
    virtual Render * getRender() = 0;

    virtual void update() = 0;
    virtual void render() = 0;

    virtual vector< wstring > getVisualSceneIDs() = 0;
    virtual wstring getDefaultVisualSceneID() = 0;

    virtual wstring getCurrentVisualSceneID() = 0;
    virtual bool setCurrentVisualScene( wstring sceneID ) = 0;

public: virtual ~Scene() {}
};

}