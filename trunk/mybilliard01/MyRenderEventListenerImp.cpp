#include "StdAfx.h"
#include "my_app.h"


MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, bRightHand_( false )
, bRowMajor_( false )
{
    scene_->load( sceneFile );
    phys_->loadXMLFile( physX_File );

    static NxMat34 posCamera( NxMat33( 
        NxVec3( 1.f, 0.f, 0.f ),
        NxVec3( 0.f, 1.f, 0.f ),
        NxVec3( 0.f, 0.f, 1.f ) ), NxVec3( -0.01f, 0.01f, -1.f ) );

    NxActor * const cameraPhysX = phys_->addCameraActor( posCamera );
    Camera * const cameraCollada = scene_->getCameraByIndex( 0u );

    camera_ = MyCameraPtr( new MyCamera( cameraCollada, cameraPhysX ) );
}

void MyRenderEventListenerImp::init( RenderBufferFactory * renderFactory )
{
    scene_->setRenderFactory( renderFactory );
    initEffect( renderFactory );
    connectPhysicsToGraphics();
}

void MyRenderEventListenerImp::initEffect( RenderBufferFactory * renderFactory )
{
    effect_ = renderFactory->createEffectShader( L"..\\asset\\SimpleSample.fx" );
    assert( effect_ );

    tech_ = effect_->createTechniqueVariable( L"RenderScene" );
    assert( effect_->isValidTechnique( tech_ ) );

    world_ = effect_->createVariable( L"g_mWorld" );
    wvp_ = effect_->createVariable( L"g_mWorldViewProjection" );
}

void MyRenderEventListenerImp::connectPhysicsToGraphics()
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );
        Node * const node = scene_->getNode( name );
        actor->userData = node;
    }
}

void MyRenderEventListenerImp::displayReset( int x, int y, int width, int height )
{
    width_ = (float) width;
    height_ = (float) height;
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime ) {
    phys_->simulate( elapsedTime );
    updateCamera( elapsedTime );
    updateObjects( elapsedTime );
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime )
{
    RowMajorMatrix44f projection;
    camera_->cameraCollada_->getProjectionMatrix44( (float*) projection, bRightHand_, true );

    RowMajorMatrix44f view;
    camera_->getViewMatrix44( (float*) view, bRightHand_, true );

    matrixProjectionView_ = projection * view;
}

void MyRenderEventListenerImp::updateObjects( float elapsedTime )
{
    toRender_.clear();

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        Node * const node = (Node *) (actor->userData);
        if( NULL == node ) continue;

        toRender_.push_back( node );

        RowMajorMatrix44f matWorld;
        actor->getGlobalPose().getRowMajor44( matWorld );
        const RowMajorMatrix44f matWVP( matrixProjectionView_ * matWorld, bRowMajor_ );
        if( bRowMajor_ ) matWorld.Transpose();

        memcpy( toRender_.rbegin()->matWorldViewProjection_, matWVP, sizeof( matWVP ) );
        memcpy( toRender_.rbegin()->matWorld_, matWorld, sizeof( matWorld ) );
    }
}

void MyRenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setNone();
    MY_FOR_EACH_MOD( ToRender, iter, toRender_ )
    {
        iter_ = iter;
        effect_->setFloatArray( world_, iter_->matWorld_, 16 );
        effect_->setFloatArray( wvp_, iter_->matWorldViewProjection_, 16 );
        render->renderWithEffectShader( effect_, tech_, this );
    }
    DXUT_EndPerfEvent();

    render->endScene();
}

void MyRenderEventListenerImp::display( Render * render, size_t pass ) {
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect display for each pass" );
    iter_->node_->display( render );
    DXUT_EndPerfEvent();
}

void MyRenderEventListenerImp::displayLost()
{
}

void MyRenderEventListenerImp::destroy() 
{
}

