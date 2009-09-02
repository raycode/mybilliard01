#pragma once
namespace my_render {


MY_INTERFACE RenderTargetCallBack {
    virtual ~RenderTargetCallBack() {}

    virtual void displayOnRenderTarget( Render * render ) PURE;

};

}