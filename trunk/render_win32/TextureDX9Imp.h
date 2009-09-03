#pragma once
namespace my_render_win32_dx9_imp {


class TextureDX9Imp : IMPLEMENTS_INTERFACE( TextureDX9 ) {
public: // from Texture
    virtual bool isFromFile() OVERRIDE;
    virtual wstring getFilename() OVERRIDE;

    virtual size_t getWidth() OVERRIDE;
    virtual size_t getHeight() OVERRIDE;

public: // from TextureDX9
    virtual SurfaceDX9 * acquireSurface( size_t level ) OVERRIDE;
    virtual bool releaseSurface( SurfaceDX9 * ) OVERRIDE;

    virtual LPDIRECT3DTEXTURE9 getTextureDX9() OVERRIDE;

public: // from ReleasableResourceDX9
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, wstring filename );
    TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height, size_t mipLevels, DWORD usage, D3DFORMAT, D3DPOOL );

private:
    LPDIRECT3DDEVICE9 getD3D9Device();
    SurfaceDX9 * findSurfaceFromAlreadyCreated( size_t level );

private:
    LPDIRECT3DDEVICE9 d3d9Device_;
    const bool bFromFile_;

    // from file
    wstring filename_;

    // from empty
    size_t requiredWidth_, requiredHeight_, requiredMipLevels_;
    DWORD requiredUsage_;
    D3DFORMAT requiredFormat_;
    D3DPOOL requiredPool_;

private:
    MY_SMART_PTR( IDirect3DTexture9 );
    IDirect3DTexture9Ptr textureDX9_;

private:
    struct SurfaceDX9Info
    {
        SurfaceDX9Ptr ptr;
        size_t level;
    };

    typedef list< SurfaceDX9Info > Surfaces;
    Surfaces surfaces_;

};


}
