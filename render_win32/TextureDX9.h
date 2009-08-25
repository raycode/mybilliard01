#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE TextureDX9
    : EXTENDS_INTERFACE( Texture )
    , EXTENDS_INTERFACE( ReleasableResourceDX9 )
{

    virtual LPDIRECT3DTEXTURE9 getTextureDX9() PURE;

};


}
