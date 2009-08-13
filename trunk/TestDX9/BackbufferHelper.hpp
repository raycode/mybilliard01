#pragma once
namespace MyTestingUtility {


class BackbufferHelper {
public:
    NxU32 * getBitPointer() {
        return bitPointer;
    }

    BackbufferHelper( Render * render )
        : render_( render )
    {
        backbuffer_ = render->getBackBuffer( 0 );
        if( NULL == backbuffer_ ) throw exception();

        SurfaceLockedRect * const locked = backbuffer_->lockRect( SurfaceLock_READONLY );
        if( NULL == locked ) throw exception();

        bitPointer = (NxU32*) locked->getBitPointer();
    }

    ~BackbufferHelper() {
        render_->releaseSurface( backbuffer_ );        
    }

private:
    Render * render_;
    Surface * backbuffer_;
    NxU32 * bitPointer;
};


}
