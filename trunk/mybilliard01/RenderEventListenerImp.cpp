#include "StdAfx.h"
#include "my_app.h"


RenderEventListenerImp::RenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, camera_( NULL )
{
    scene_->load( sceneFile );
    phys_->loadColladaFile( physX_File );
    // scene_->getCemeraByIndex( 0 );
}

void RenderEventListenerImp::init( RenderBufferFactory * renderFactory )
{
    scene_->setRenderFactory( renderFactory );

    effect_ = renderFactory->createEffectShader( L"..\\asset\\SimpleSample.fx" );
    assert( effect_ );

    tech_ = effect_->createTechniqueVariable( L"RenderScene" );
    assert( effect_->isValidTechnique( tech_ ) );

    wvp_ = effect_->createVariable( L"g_mWorldViewProjection" );
}

void RenderEventListenerImp::displayReset( int x, int y, int width, int height )
{}

void RenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime ) {
    phys_->simulate( elapsedTime );
    toRender_.clear();
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );
        Node * const node = scene_->getNode( name );
        if( NULL == node ) continue;

        toRender_.push_back( node );
        actor->getGlobalPose().getRowMajor44( toRender_.rbegin()->worldMatrix_ );
    }
    phys_->fetchResult();
}

void RenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"My Testing" ); // These events are to help PIX identify
    render->setRenderState()->setWireframe()->setWired();
    render->setRenderState()->setCull()->setNone();

    MY_FOR_EACH( ToRender, iter, toRender_ )
    {
        iter_ = iter;
        render->renderWithEffectShader( effect_, tech_, this );
    }
    DXUT_EndPerfEvent();

    render->endScene();
}

void RenderEventListenerImp::display( Render * render, size_t pass ) {
    effect_->setFloatArray( wvp_, iter_->worldMatrix_, 16 );
    iter_->node_->display( render );
}

void RenderEventListenerImp::displayLost()
{
}

void RenderEventListenerImp::destroy() 
{
}

