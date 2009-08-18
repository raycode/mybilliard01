#pragma once
namespace my_render {


MY_INTERFACE Surface {
    virtual ~Surface() {}
    
#define SurfaceLock_READONLY           0x00000010L
#define SurfaceLock_DISCARD            0x00002000L
#define SurfaceLock_NOOVERWRITE        0x00001000L
#define SurfaceLock_NOSYSLOCK          0x00000800L
#define SurfaceLock_DONOTWAIT          0x00004000L                  
#define SurfaceLock_NO_DIRTY_UPDATE    0x00008000L

    virtual SurfaceLockedRect * lockRect( int left, int top, int right, int bottom, int flag ) PURE;
    virtual SurfaceLockedRect * lockRect( int flag ) PURE;

    virtual bool isLocked() PURE;

    virtual void unlockRect( SurfaceLockedRect * ) PURE;

};


}
