#pragma once
namespace my_render {

INTERFACE_ Scene {
public:
    virtual bool load( wstring filename ) = 0;

    virtual void setRender( Render * render ) = 0;
    virtual Render * getRender() = 0;

    virtual void update() = 0;
    virtual void render() = 0;

public: virtual ~Scene() {}
};

}