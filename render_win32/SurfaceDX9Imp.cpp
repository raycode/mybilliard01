#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


SurfaceDX9Imp::SurfaceDX9Imp( IDirect3DSurface9 * surface )
: dx9Surface_( surface )
{
    if( NULL == surface ) throw exception();
}

SurfaceDX9Imp::~SurfaceDX9Imp()
{
    if( isLocked() )
        unlockRect( NULL );

    dx9Surface_->Release();
}

bool SurfaceDX9Imp::acquireResource()
{
    return false;
}

void SurfaceDX9Imp::releaseResource()
{
}



SurfaceLockedRect * SurfaceDX9Imp::lockRect( int left, int top, int right, int bottom, int flag )
{
    RECT * rect = NULL;
    if( false == (0 == left && 0 == right && 0 == top && 0 == bottom ) ) {
        rect = new RECT();
        ::SetRect( rect, left, top, right, bottom );
    }

    D3DLOCKED_RECT dxLockedRect;
    const HRESULT hr = dx9Surface_->LockRect( &dxLockedRect, rect, flag );
    SAFE_DELETE( rect );
    if( FAILED( hr ) ) {
        DXUT_ERR( L"SurfaceDX9Imp::lockRect", hr );
       return NULL;
    }

    SurfaceLockedRectDX9Imp * const lockedRect = new SurfaceLockedRectDX9Imp( dxLockedRect );
    lockedRect_ = SurfaceLockedRectDX9ImpPtr( lockedRect );
    return lockedRect;
}

SurfaceLockedRect * SurfaceDX9Imp::lockRect( int flag )
{
    return lockRect( 0, 0, 0, 0, flag );
}

bool SurfaceDX9Imp::isLocked()
{
    return NULL != lockedRect_;
}

void SurfaceDX9Imp::unlockRect( SurfaceLockedRect * lockedRect )
{
    const HRESULT hr = dx9Surface_->UnlockRect();
    if( FAILED( hr ) )
        DXUT_ERR( L"SurfaceDX9Imp::unlockRect", hr );

    lockedRect_ = SurfaceLockedRectDX9ImpPtr( (SurfaceLockedRectDX9Imp *) NULL );
}


}