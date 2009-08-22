#include "StdAfx.h"
#include "my_app.h"


MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, bRightHandHardware_( false )
{
    const bool bScene = scene_->load( sceneFile );
    const bool bPhys = phys_->loadXMLFile( physX_File );
    assert( bScene );
    assert( bPhys );

    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, &*phys_,
            NxVec3( -80.f, 0.f, 50.f ), NxVec3( 1.f, 0.f, -0.5f ), bRightHandHardware_ ) );
    camera_->setMovementToFixedHeight( 50.f );
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

    world_ = effect_->createVariableByName( L"g_mWorld" );
    wvp_ = effect_->createVariableByName( L"g_mWorldViewProjection" );
}

void MyRenderEventListenerImp::connectPhysicsToGraphics()
{
    wchar_t tmp[256];
    _snwprintf_s( tmp, 256, L"%d physics actors are found\n", phys_->getNumberOfActors() );
    OutputDebugStr( tmp );

    size_t numberOfLoad = 0;
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );
        Node * const node = scene_->getNode( name );
        actor->userData = node;
        if( NULL != node ) ++numberOfLoad;
    }

    _snwprintf_s( tmp, 256, L"%d geometry nodes are found\n", numberOfLoad );
    OutputDebugStr( tmp );
}

void MyRenderEventListenerImp::displayReset( int x, int y, int width, int height )
{
    updateCameraProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::updateCameraProjection( float aspectRatio )
{
    camera_->setAspect( aspectRatio );
    camera_->getProjectionMatrix44( matrixProjection_, bRightHandHardware_, true );
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( elapsedTime );
    updateCamera( elapsedTime );
    updateCameraView();
    updateObjects( elapsedTime );
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime ) {
    camera_->update( elapsedTime );
}
void MyRenderEventListenerImp::updateCameraView()
{
    RowMajorMatrix44f view;
    camera_->getViewMatrix44( view, true );
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
    render->setRenderState()->setCull()->setClockWise();
    MY_FOR_EACH_MOD( ToRender, iter, toRenders_ )
    {
        iter_ = iter;
        world_->setFloatArray( iter_->matWorld_, 16u );
        wvp_->setFloatArray( iter_->matWorldViewProjection_, 16u );
        effect_->renderWithTechnique( this );
    }
    DXUT_EndPerfEvent();

    render->endScene();
}

void MyRenderEventListenerImp::displayPass( size_t pass ) {
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"Effect display for each pass" );
    iter_->node_->display();
    DXUT_EndPerfEvent();
}

void MyRenderEventListenerImp::displayLost()
{
}

void MyRenderEventListenerImp::destroy() 
{
}

MyCamera * MyRenderEventListenerImp::getMyCamera() {
    return &* camera_;
}
