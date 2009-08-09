#include "DXUT.h"
#include "RenderForDX9.h"


void RenderEventListenerImp::display( Render * render ) {
}

void RenderEventListenerImp::displayChanged( Render * render, bool modeChanged, bool deviceChanged) {

}

void RenderEventListenerImp::init( Render * render ) {
    render->setScreenWidth( 640 );
    render->setScreenHeight( 480 );
    render->openWindow( ConstString::windowTitle(), true );
}

void RenderEventListenerImp::reshape( Render * redner, int x, int y, int width, int height ) {

}


