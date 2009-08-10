#include "DXUT.h"
#include "RenderForDX9.h"


void RenderErrorListenerImp::createWindow( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

void RenderErrorListenerImp::createDevice( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

