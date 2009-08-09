#include "DXUT.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {


void RenderErrorNotifyImp::openWindow( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

}
