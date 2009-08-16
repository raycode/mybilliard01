#pragma once
namespace my_render {


MY_INTERFACE RenderEffectShader {
    virtual ~RenderEffectShader() {}

    virtual void display( Render *, size_t pass ) = 0;

};


}
