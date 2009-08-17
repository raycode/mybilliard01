#pragma once
namespace MyTestingUtility {


class BackbufferHelper {
public:
    NxU32 * getBitPointer() {
        return bitPointer;
    }

    BackbufferHelper( RenderBufferFactory * factory )
        : factory_( factory )
    {
        backBuffer_ = factory->getBackBuffer( 0 );
        if( NULL == backBuffer_ ) throw exception();

        SurfaceLockedRect * const locked = backBuffer_->lockRect( SurfaceLock_READONLY );
        if( NULL == locked ) throw exception();

        bitPointer = (NxU32*) locked->getBitPointer();
    }

    ~BackbufferHelper() {
        factory_->destroySurface( backBuffer_ );        
    }

private:
    RenderBufferFactory * factory_;
    Surface * backBuffer_;
    NxU32 * bitPointer;
};


}
