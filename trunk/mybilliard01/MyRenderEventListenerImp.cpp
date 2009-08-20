#include "StdAfx.h"
#include "my_app.h"


MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, bRightHand_( true )
{
    scene_->load( sceneFile );
    phys_->loadXMLFile( physX_File );

    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, &*phys_, NxVec3( -0.01f, 0.01f, -1.f ) ) );
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
    updateCameraProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::updateCameraProjection( float aspectRatio )
{
    camera_->setAspect( aspectRatio );
    camera_->getProjectionMatrix44( matrixProjection_, bRightHand_, true );
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( elapsedTime );
    updateCharacter();
    updateCameraView();
    updateObjects( elapsedTime );
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCharacter()
{
    phys_->UpdateControllers();
    camera_->move( -0.5f, -0.5f, 0.f, 0.1f);
}

void MyRenderEventListenerImp::updateCameraView()
{
    RowMajorMatrix44f view;
    camera_->getViewMatrix44( view, bRightHand_, true );
    matrixProjectionView_ = matrixProjection_ * view;
}

void MyRenderEventListenerImp::updateObjects( float elapsedTime )
{
    toRenders_.clear();

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        Node * const node = (Node *) (actor->userData);
        if( NULL == node ) continue;

        toRenders_.push_back( node );
        GeometryUnderEffect * const toRender = &*(toRenders_.rbegin());

        RowMajorMatrix44f matWorld;
        actor->getGlobalPose().getRowMajor44( matWorld );

        matWorld.GetColumnMajor( toRender->matWorld_ );
        (matrixProjectionView_ * matWorld).GetColumnMajor( toRender->matWorldViewProjection_ );
    }
}

void MyRenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setNone();
    MY_FOR_EACH_MOD( ToRender, iter, toRenders_ )
    {
        iter_ = iter;
        effect_->setFloatArray( world_, iter_->matWorld_, 16u );
        effect_->setFloatArray( wvp_, iter_->matWorldViewProjection_, 16u );
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

