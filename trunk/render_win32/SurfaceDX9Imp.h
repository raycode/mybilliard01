#pragma once
namespace my_render_win32_dx9_imp {


class SurfaceDX9Imp : IMPLEMENTS_INTERFACE( SurfaceDX9 ) {
public: // from SurfaceDX9
    virtual SurfaceLockedRectDX9 * lockRect( int left, int top, int right, int bottom, int flag ) OVERRIDE;
    virtual SurfaceLockedRectDX9 * lockWhole( int flag ) OVERRIDE;
 
    virtual bool isLocked() OVERRIDE;

    virtual void unlock( SurfaceLockedRectDX9 * ) OVERRIDE;

    virtual LPDIRECT3DSURFACE9 getSurfaceDX9() OVERRIDE;

public:
    SurfaceDX9Imp( IDirect3DSurface9Ptr );

private:
    IDirect3DSurface9Ptr dx9Surface_;
    SurfaceLockedRectDX9Ptr lockedRect_;
};


}
