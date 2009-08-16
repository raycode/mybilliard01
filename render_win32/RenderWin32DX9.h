#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE RenderWin32DX9 : EXTENDS_INTERFACE_( RenderWin32 ) {

    virtual LPDIRECT3DDEVICE9 getD3D9Device() = 0;

    virtual void setBackbufferLockable( bool ) = 0;
    virtual bool isBackbufferLockable() = 0;

};


}