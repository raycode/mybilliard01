#pragma once
namespace my_render {


MY_INTERFACE RenderTarget {
    virtual ~RenderTarget() {}

    virtual bool displayOnRenderTarget( Render * render, RenderTargetCallBack * ) PURE;

    virtual Texture * getRenderTargetTexture() PURE;

};

}