#include "DXUT.h"
#include "my_app.h"



RenderEventListenerImp::RenderEventListenerImp()
{
}

void RenderEventListenerImp::init( Render * render )
{
    initDXUT( render );
}

void RenderEventListenerImp::destroy( Render * render )
{
    destroyDXUT();
}

void RenderEventListenerImp::displayReset( Render * render, int x, int y, int width, int height )
{
    displayResetDXUT( render, width, height );
}

void RenderEventListenerImp::displayLost( Render * render )
{
    displayLostDXUT();
}

void RenderEventListenerImp::update( float elapsedTime ) {
}

void RenderEventListenerImp::display( Render * render ) {
    render->clear( ERenderClear_TARGET | ERenderClear_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 );
    if( false == render->beginScene() ) return;

    // TODO for collada 

    displayDXUT();
    render->endScene();
}


