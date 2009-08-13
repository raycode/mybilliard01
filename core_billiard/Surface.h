#pragma once
namespace my_render {


INTERFACE_ Surface {
public:
    
#define SurfaceLock_READONLY           0x00000010L
#define SurfaceLock_DISCARD            0x00002000L
#define SurfaceLock_NOOVERWRITE        0x00001000L
#define SurfaceLock_NOSYSLOCK          0x00000800L
#define SurfaceLock_DONOTWAIT          0x00004000L                  
#define SurfaceLock_NO_DIRTY_UPDATE    0x00008000L

    virtual SurfaceLockedRect * lockRect( int left, int top, int right, int bottom, int flag ) = 0;
    virtual SurfaceLockedRect * lockRect( int flag ) = 0;

    virtual bool isLocked() = 0;

    virtual void unlockRect( SurfaceLockedRect * ) = 0;

public: virtual ~Surface() {}
};


}
