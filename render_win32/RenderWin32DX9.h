#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE RenderWin32DX9 : EXTENDS_INTERFACE( RenderWin32 ) {

    virtual LPDIRECT3DDEVICE9 getD3D9Device() PURE;

    virtual void setBackbufferLockable( bool ) PURE;
    virtual bool isBackbufferLockable() PURE;

};


}