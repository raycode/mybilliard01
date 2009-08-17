#include "StdAfx.h"
#include "my_app.h"


const static float positions[] = {
    0.5f, 0.2f, 0.5f,
    0.8f, 0.8f, 0.5f,
    0.3f, 0.8f, 0.5f
};

const static NxU32 diffuses[] = {
    0xffff0000, 0xff00ff00, 0xff00ffff
};


static wstring getFilename() {
    return ( L"..\\asset\\SimpleSample.fx" );
}

RenderEventListenerImp::RenderEventListenerImp()
{
}

void RenderEventListenerImp::init( RenderBufferFactory * factory )
{
    effect_ = factory->createEffectShader( getFilename() );
    assert( effect_ );

    tech_ = effect_->createTechniqueVariable( L"RenderScene" );
    assert( effect_->isValidTechnique( tech_ ) );

    vb_ = factory->createVertexBuffer_static( 3, positions );
    vb_->appendColor_Array( diffuses, 0 );

    wvp_ = effect_->createVariable( L"g_mWorldViewProjection" );
}

void RenderEventListenerImp::displayReset( int x, int y, int width, int height )
{
}

void RenderEventListenerImp::update( RenderBufferFactory *, float elapsedTime )
{
    D3DXMATRIX wvp;

    effect_->setFloatArray( wvp_, wvp, 16 );
}

void RenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"My Testing" ); // These events are to help PIX identify
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setNone();
    render->renderWithEffectShader( effect_, tech_, this );
    DXUT_EndPerfEvent();

    render->endScene();
}

void RenderEventListenerImp::display( Render * render, size_t pass ) {
    render->drawPrimitive_TRIANGLELIST( vb_, 0, 1 );
}

void RenderEventListenerImp::displayLost()
{
}

void RenderEventListenerImp::destroy() 
{
}

