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

    initCamera( NxVec3( -80.f, 0.f, 50.f ), NxVec3( 1.f, 0.f, -0.5f ) );
}

void MyRenderEventListenerImp::initCamera( NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, phys_.get(), pos, dir, bRightHandHardware_ ) );
    camera_->setMovementToFixedHeight( pos.z );
}

void MyRenderEventListenerImp::init()
{
}

void MyRenderEventListenerImp::displayReset( RenderBufferFactory * renderFactory, int x, int y, int width, int height ) {
    initEffect( renderFactory );
    scene_->setRenderFactory( renderFactory );
    updateCameraProjection( (float) width / (float) height );
    updateEffectProjection();
}

void MyRenderEventListenerImp::initEffect( RenderBufferFactory * renderFactory )
{
    wchar_t tmp[256];
    _snwprintf_s( tmp, 256, L"%d physics actors are found\n", phys_->getNumberOfActors() );
    OutputDebugStr( tmp );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );

        const wstring nodeName = convertString( actor->getName() );
        Node * const node = scene_->getNode( nodeName );

        actor->userData = createEffectFeeder( node, renderFactory );
    }

    createSharedVariableFeeder();

    initEffectLights();
}

void MyRenderEventListenerImp::initEffectLights() {
    const float light0_position[] = { -40.f, 0.f, 80.f, 1.f };
    getSharedVariable( L"Light0_Position" )->setFloatArray( light0_position, 4u );
}

void MyRenderEventListenerImp::updateCameraProjection( float aspectRatio ) {
    camera_->setAspect( aspectRatio );
    camera_->getProjectionMatrix44( matrixProjection_, bRightHandHardware_, true );
}

void MyRenderEventListenerImp::updateEffectProjection()
{
    sharedVaribleFeeder_->updateProjection( matrixProjection_ );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateProjection( matrixProjection_ );
    }
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( elapsedTime );
    updateCamera( elapsedTime );
    updateEffect( elapsedTime );
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( float elapsedTime ) {
    camera_->update( elapsedTime );
    updateCameraView();
    updateCameraPosAndDir();
}

void MyRenderEventListenerImp::updateCameraView()
{
    camera_->getViewMatrix44( matrixView_, true );
    matrixProjectionView_ = matrixProjection_ * matrixView_;
}

void MyRenderEventListenerImp::updateCameraPosAndDir()
{
    NxExtendedVec3 pos = camera_->getPosition();
    cameraPos_.x = (NxReal) pos.x;
    cameraPos_.y = (NxReal) pos.y;
    cameraPos_.z = (NxReal) pos.z;
    cameraDir_ = camera_->getDirectionVector();
}

void MyRenderEventListenerImp::updateEffect( float elapsedTime )
{
    sharedVaribleFeeder_->updateMatrix( NULL, cameraPos_, cameraDir_,
        matrixView_, matrixProjectionView_ );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateMatrix( actor, cameraPos_, cameraDir_,
            matrixView_, matrixProjectionView_ );
    }
}

void MyRenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify
    {
        render->setRenderState()->setWireframe()->setSolid();
        render->setRenderState()->setCull()->setClockWise();
        MY_FOR_EACH_MOD( EffectShaderFeeders, iter, feeders_ )
            (*iter)->display();
    }
    DXUT_EndPerfEvent();

    render->endScene();
}   

void MyRenderEventListenerImp::displayLost() {
    sharedVariables_.clear();
    feeders_.clear();
}

void MyRenderEventListenerImp::destroy() 
{
}

MyCamera * MyRenderEventListenerImp::getMyCamera() {
    return camera_.get();
}
