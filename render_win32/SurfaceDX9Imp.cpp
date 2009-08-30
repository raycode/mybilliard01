#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


SurfaceDX9Imp::SurfaceDX9Imp( IDirect3DSurface9Ptr surface )
: dx9Surface_( surface )
{
    if( NULL == surface ) throw exception();
}

SurfaceLockedRectDX9 * SurfaceDX9Imp::lockRect( int left, int top, int right, int bottom, int flag )
{
    RECT * rect = NULL;
    if( false == ( left == right && top == bottom ) ) {
        rect = new RECT();
        ::SetRect( rect, left, top, right, bottom );
    }

    D3DLOCKED_RECT dxLockedRect;
    const HRESULT hr = dx9Surface_->LockRect( &dxLockedRect, rect, flag );
    SAFE_DELETE( rect );
    RETURN_NULL_IF_FAILED( hr, L"SurfaceDX9Imp::lockRect" );

    lockedRect_ = SurfaceLockedRectDX9Ptr( new SurfaceLockedRectDX9Imp( dxLockedRect ), SurfaceDX9::Unlocker( this ) );
    return lockedRect_.get();
}

SurfaceLockedRectDX9 * SurfaceDX9Imp::lockWhole( int flag ) {
    return lockRect( 0, 0, 0, 0, flag );
}

bool SurfaceDX9Imp::isLocked() {
    return NULL != lockedRect_;
}

void SurfaceDX9Imp::unlock( SurfaceLockedRectDX9 * lockedRect )
{
    const HRESULT hr = dx9Surface_->UnlockRect();
    if( FAILED( hr ) )
        DXUT_ERR( L"SurfaceDX9Imp::unlock", hr );

    lockedRect_.reset();
}

LPDIRECT3DSURFACE9 SurfaceDX9Imp::getSurfaceDX9() {
    return dx9Surface_.get();
}

}