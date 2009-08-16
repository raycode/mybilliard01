#pragma once
namespace my_render {


NULL_OBJECT( RenderState_Wireframe ) {

    virtual void setSolid() OVERRIDE {}
    virtual void setWired() OVERRIDE {}

    virtual bool isSolid() const OVERRIDE { return false; }

};

}