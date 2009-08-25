#pragma once
namespace my_render_win32_dx9_imp {


class TextureDX9Imp : IMPLEMENTS_INTERFACE( TextureDX9 ) {
public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public: // from TextureDX9
    virtual LPDIRECT3DTEXTURE9 getTextureDX9() OVERRIDE;

public:
    TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, wstring filename );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();

private:
    const wstring filename_;
    LPDIRECT3DDEVICE9 d3d9Device_;

private:
    MY_SMART_PTR( IDirect3DTexture9 );
    IDirect3DTexture9Ptr textureDX9_;

};


}
