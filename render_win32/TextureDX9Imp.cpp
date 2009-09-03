#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


TextureDX9Imp::TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, wstring filename )
: d3d9Device_( d3d9Device )
, bFromFile_( true )
, filename_( filename )
{
}

TextureDX9Imp::TextureDX9Imp( LPDIRECT3DDEVICE9 d3d9Device, size_t width, size_t height, size_t mipLevels, DWORD usage, D3DFORMAT format, D3DPOOL pool )
: d3d9Device_( d3d9Device )
, bFromFile_( false )
, requiredWidth_( width )
, requiredHeight_( height )
, requiredMipLevels_( mipLevels )
, requiredUsage_( usage )
, requiredFormat_( format )
, requiredPool_( pool )
{
}


bool TextureDX9Imp::acquireResource()
{
    if( NULL != textureDX9_ ) return true;

    LPDIRECT3DTEXTURE9 newTexDX9;
    if( isFromFile() )
    {
        const HRESULT hr = D3DXCreateTextureFromFileEx( getD3D9Device(), filename_.c_str(),
            D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
            D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
            0, NULL, NULL, & newTexDX9 );
        RETURN_FALSE_IF_FAILED( hr, L"TextureDX9Imp::acquireResource" );
    }
    else
    {
        const HRESULT hr = D3DXCreateTexture( getD3D9Device(),
            requiredWidth_, requiredHeight_, requiredMipLevels_, requiredUsage_,
            requiredFormat_, requiredPool_, & newTexDX9 );
        RETURN_FALSE_IF_FAILED( hr, L"TextureDX9Imp::acquireResource" );
    }

    textureDX9_ = IDirect3DTexture9Ptr( newTexDX9, ComReleaser< IDirect3DTexture9 >() );

    MY_FOR_EACH( Surfaces, iter, surfaces_ )
        acquireSurface( iter->level );
    return true;
}

void TextureDX9Imp::releaseResource() {
    MY_FOR_EACH_MODIFY( Surfaces, iter, surfaces_ )
        iter->ptr.reset();
    textureDX9_.reset();
}

LPDIRECT3DDEVICE9 TextureDX9Imp::getD3D9Device() {
    return d3d9Device_;
}

LPDIRECT3DTEXTURE9 TextureDX9Imp::getTextureDX9() {
    return textureDX9_.get();
}

SurfaceDX9 * TextureDX9Imp::acquireSurface( size_t level ) 
{
    {
        SurfaceDX9 * const alreadyCreated = findSurfaceFromAlreadyCreated( level );
        if( NULL != alreadyCreated ) return alreadyCreated;
    }

    IDirect3DSurface9 * newSurfaceDX9;
    const HRESULT hr = getTextureDX9()->GetSurfaceLevel( level, & newSurfaceDX9 );
    RETURN_NULL_IF_FAILED( hr, L"TextureDX9Imp::acquireSurface" );

    SurfaceDX9Info tmp;
    tmp.level = level;
    tmp.ptr = SurfaceDX9Ptr( new SurfaceDX9Imp( IDirect3DSurface9Ptr( newSurfaceDX9, ComReleaser< IDirect3DSurface9 >() ) ) );
    surfaces_.push_back( tmp );
    return tmp.ptr.get();
}

bool TextureDX9Imp::releaseSurface( SurfaceDX9 * surface )  {
    MY_FOR_EACH_MODIFY( Surfaces, iter, surfaces_ ) {
        if( iter->ptr.get() == surface ) {
            surfaces_.erase( iter );
            return true;
        }
    }
    return false;
}

SurfaceDX9 * TextureDX9Imp::findSurfaceFromAlreadyCreated( size_t level )
{
    MY_FOR_EACH( Surfaces, iter, surfaces_ )
        if( iter->level == level && NULL != iter->ptr ) return iter->ptr.get();
    return NULL;
}

bool TextureDX9Imp::isFromFile() {
    return bFromFile_;
}
wstring TextureDX9Imp::getFilename() {
    return filename_;
}

size_t TextureDX9Imp::getWidth() {
    D3DSURFACE_DESC desc;
    textureDX9_->GetLevelDesc( 0, & desc );
    return desc.Width;
}

size_t TextureDX9Imp::getHeight() {
    D3DSURFACE_DESC desc;
    textureDX9_->GetLevelDesc( 0, & desc );
    return desc.Height;
}


}