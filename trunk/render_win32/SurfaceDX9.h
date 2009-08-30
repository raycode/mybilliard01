#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE SurfaceDX9 {
    virtual ~SurfaceDX9() {}

#define SurfaceLock_READONLY           0x00000010L
#define SurfaceLock_DISCARD            0x00002000L
#define SurfaceLock_NOOVERWRITE        0x00001000L
#define SurfaceLock_NOSYSLOCK          0x00000800L
#define SurfaceLock_DONOTWAIT          0x00004000L                  
#define SurfaceLock_NO_DIRTY_UPDATE    0x00008000L

    virtual SurfaceLockedRectDX9 * lockRect( int left, int top, int right, int bottom, int flag ) PURE;
    virtual SurfaceLockedRectDX9 * lockWhole( int flag ) PURE;

    virtual bool isLocked() PURE;

    virtual void unlock( SurfaceLockedRectDX9 * ) PURE;

    virtual LPDIRECT3DSURFACE9 getSurfaceDX9() PURE;

public:
    struct Unlocker
    {
        void operator()( SurfaceLockedRectDX9 * lockedRect ) { owner_->unlock( lockedRect ); }
        Unlocker( SurfaceDX9 * owner ) : owner_( owner ) {}
        SurfaceDX9 * const owner_;
    };

};


MY_SMART_PTR( IDirect3DSurface9 );


}