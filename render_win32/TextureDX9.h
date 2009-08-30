#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE TextureDX9
    : EXTENDS_INTERFACE( Texture )
    , EXTENDS_INTERFACE( ReleasableResourceDX9 )
{

    virtual SurfaceDX9 * acquireSurface( size_t level ) PURE;
    virtual bool releaseSurface( SurfaceDX9 * ) PURE;

    virtual LPDIRECT3DTEXTURE9 getTextureDX9() PURE;

public:
    struct Releaser
    {
        void operator()( SurfaceDX9 * surface ) { owner_->releaseSurface( surface ); }
        Releaser( TextureDX9 * owner ) : owner_( owner ) {}
        TextureDX9 * const owner_;
    };

};


}
