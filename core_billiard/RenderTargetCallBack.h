#pragma once
namespace my_render {


MY_INTERFACE RenderTargetCallBack {
    virtual ~RenderTargetCallBack() {}

    virtual void displayOnRenderTargetCallBack( Render * render ) PURE;

};

}