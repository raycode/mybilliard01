#include "StdAfx.h"
#include "my_app.h"


void RenderErrorListenerImp::createWindow( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

void RenderErrorListenerImp::createDevice( wstring msg ) {
    ::OutputDebugStr( msg.c_str() );
}

