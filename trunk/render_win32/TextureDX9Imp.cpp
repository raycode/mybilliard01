#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


TextureDX9Imp::TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, wstring filename )
: filename_( filename )
, d3d9Device_( d3d9Device )
{
}

bool TextureDX9Imp::acquireResource()
{
    LPDIRECT3DTEXTURE9 newTexDX9;
    const HRESULT hr = D3DXCreateTextureFromFile( getD3D9Device(), filename_.c_str(), & newTexDX9 );
    RETURN_FALSE_IF_FAILED( hr, L"TextureDX9Imp::acquireResource" );

    textureDX9_ = IDirect3DTexture9Ptr( newTexDX9, ComReleaser< IDirect3DTexture9 >() );
    return true;
}

void TextureDX9Imp::releaseResource() {
    textureDX9_.reset();
}

LPDIRECT3DDEVICE9 TextureDX9Imp::getD3D9Device() {
    return d3d9Device_;
}

LPDIRECT3DTEXTURE9 TextureDX9Imp::getTextureDX9() {
    return textureDX9_.get();
}

bool TextureDX9Imp::isFromFile() {
    return true;
}
wstring TextureDX9Imp::getFilename() {
    return filename_;
}


}