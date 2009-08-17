#pragma once
namespace my_render_win32_dx9_imp {


class SurfaceDX9Imp : IMPLEMENTS_INTERFACE( SurfaceDX9 ) {
public: // from Surface
    virtual SurfaceLockedRect * lockRect( int left, int top, int right, int bottom, int flag ) OVERRIDE;
    virtual SurfaceLockedRect * lockRect( int flag ) OVERRIDE;
 
    virtual bool isLocked() OVERRIDE;

    virtual void unlockRect( SurfaceLockedRect * ) OVERRIDE;

public: // from ReleasableResource
    virtual bool acquireResource() OVERRIDE;
    virtual void releaseResource() OVERRIDE;

public:
    SurfaceDX9Imp( IDirect3DSurface9 * );
    ~SurfaceDX9Imp();

private:
    IDirect3DSurface9 * const dx9Surface_;
    SurfaceLockedRectDX9ImpPtr lockedRect_;
};


}
