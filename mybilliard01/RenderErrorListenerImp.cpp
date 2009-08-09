#include "DXUT.h"
#include "RenderForDX9.h"


void RenderErrorListenerImp::openWindow( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

