#pragma once
namespace my_render_win32_dx9_imp {


class SurfaceLockedRectDX9Imp : IMPLEMENTS_( SurfaceLockedRect ) {
public: // from SurfaceLockedRect
    virtual int getPitch() OVERRIDE;
    virtual void * getBitPointer() OVERRIDE;

public:
    SurfaceLockedRectDX9Imp( const D3DLOCKED_RECT & dxLockedRect );

private:
    D3DLOCKED_RECT dxLockedRect_;
};


}
