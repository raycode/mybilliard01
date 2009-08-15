#pragma once
namespace my_render {


INTERFACE_ RenderEffectShader {
public:
    virtual void render( Render *, size_t pass ) = 0;

public: virtual ~RenderEffectShader() {}
};


}
