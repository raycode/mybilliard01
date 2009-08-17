#include "StdAfx.h"
#include "my_app.h"


const static float positions[] = {
    150.0f,  50.0f, 0.5f,
    250.0f, 250.0f, 0.5f,
    50.0f, 250.0f, 0.5f
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
    //vb_->appendNormal_Array( positions, 0 );
    //vb_->appendColor_Array( diffuses, 0 );

    //wvp_ = effect_->createVariable( L"g_mWorldViewProjection" );
    //world_ = effect_->createVariable( L"g_mWorld" );
    //time_ = effect_->createVariable( L"g_fTime" );

    //D3DXVECTOR3 vecEye( 0.0f, 0.0f, -5.0f );
    //D3DXVECTOR3 vecAt ( 0.0f, 0.0f, -0.0f );
    //camera_.SetViewParams( &vecEye, &vecAt );
}

void RenderEventListenerImp::displayReset( int x, int y, int width, int height )
{
    //float fAspectRatio = width / ( float ) height;
    //camera_.SetProjParams( D3DX_PI / 4, fAspectRatio, 0.1f, 1000.0f );
    //camera_.SetWindow( width, height );
}

void RenderEventListenerImp::update( RenderBufferFactory *, float elapsedTime )
{
    //D3DXMATRIXA16 mWorld;
    //D3DXMATRIXA16 mView;
    //D3DXMATRIXA16 mProj;
    //D3DXMATRIXA16 mWorldViewProjection;

    //mWorld = *camera_.GetWorldMatrix();
    //mProj = *camera_.GetProjMatrix();
    //mView = *camera_.GetViewMatrix();

    //effect_->setFloatArray( wvp_, (float*) &mWorldViewProjection, 16 );
    //effect_->setFloatArray( world_, (float*) &mWorld, 16 );
    //effect_->setFloat( time_, elapsedTime );
}

void RenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    //if( false == render->beginScene() ) return;

    //render->setRenderState()->setWireframe()->setSolid();
    //render->renderWithEffectShader( effect_, tech_, this );
    //
    //render->endScene();
}

void RenderEventListenerImp::display( Render * render, size_t pass ) {
    //render->drawPrimitive_TRIANGLELIST( vb_, 0, 1 );
}

void RenderEventListenerImp::displayLost()
{
}

void RenderEventListenerImp::destroy() 
{
}

