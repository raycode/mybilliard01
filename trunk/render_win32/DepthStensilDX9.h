#pragma once
namespace my_render_win32_dx9 {


MY_INTERFACE DepthStensilDX9 : EXTENDS_INTERFACE( ReleasableResourceDX9 ) {

    virtual SurfaceDX9 * getSurfaceDX9() PURE;

};

}