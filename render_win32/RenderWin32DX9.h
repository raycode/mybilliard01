#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE RenderWin32DX9 : EXTENDS_INTERFACE( RenderWin32 ) {

    virtual LPDIRECT3DDEVICE9 getD3D9Device() PURE;

    virtual SurfaceDX9 * acquireBackBuffer( size_t whichBackBuffer ) PURE;
    virtual bool releaseBackBuffer( SurfaceDX9 * backBuffer ) PURE;

    virtual void setBackbufferLockable( bool ) PURE;
    virtual bool isBackbufferLockable() PURE;

public:
    struct Releaser
    {
        void operator()( SurfaceDX9 * backBuffer ) { owner_->releaseBackBuffer( backBuffer ); }
        Releaser( RenderWin32DX9 * owner ) : owner_( owner ) {}
        RenderWin32DX9 * const owner_;
    };

};


}