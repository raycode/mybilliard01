#include "DXUT.h"
#include "my_render_win32_dx9_imp.h"
namespace my_render_win32_dx9_imp {


SurfaceLockedRectDX9Imp::SurfaceLockedRectDX9Imp( const D3DLOCKED_RECT & dxLockedRect )
: dxLockedRect_( dxLockedRect )
{
}

int SurfaceLockedRectDX9Imp::getPitch() {
    return dxLockedRect_.Pitch;
}

void * SurfaceLockedRectDX9Imp::getBitPointer() {
    return dxLockedRect_.pBits;
}


}