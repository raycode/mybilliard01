#pragma once
namespace my_render {


MY_INTERFACE RenderTarget {
    virtual ~RenderTarget() {}

    virtual bool display( Render * render, RenderTargetCallBack * ) PURE;

    virtual Texture * getTexture() PURE;

};

}