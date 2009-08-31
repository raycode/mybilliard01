#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE RenderTargetDX9
    : EXTENDS_INTERFACE( RenderTarget )
    , EXTENDS_INTERFACE( ReleasableResourceDX9 )
{

    virtual TextureDX9 * getTextureDX9() PURE;
    virtual DepthStensilDX9 * getDepthStensilDX9() PURE;

};

}
