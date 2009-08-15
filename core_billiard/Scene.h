#pragma once
namespace my_render {

INTERFACE_ Scene {
public:
    virtual bool load( wstring filename, Factory * factory ) = 0;

    virtual void update() = 0;
    virtual void render( Render * ) = 0;

    virtual vector< const wchar_t * > getVisualSceneIDs() = 0;
    virtual const wchar_t * getDefaultVisualSceneID() = 0;

    virtual const wchar_t * getCurrentVisualSceneID() = 0;
    virtual bool setCurrentVisualScene( wstring sceneID ) = 0;

public: virtual ~Scene() {}
};

}