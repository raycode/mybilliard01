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
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, &*phys_, pos, dir, bRightHandHardware_ ) );
    camera_->setMovementToFixedHeight( pos.z );
}

void MyRenderEventListenerImp::init( RenderBufferFactory * renderFactory )
{
    initEffect( renderFactory );
    scene_->setRenderFactory( renderFactory );
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

        actor->userData = createToRender( node, renderFactory );
    }
}

ToRender * MyRenderEventListenerImp::createToRender( Node * node, RenderBufferFactory * renderFactory )
{
    if( NULL == node ) return & nullToRender_;
    const wstring nodeName = node->getName();

    const wstring effectFilename = ConstEffectFilename::getEffectFilenameByNodeName( nodeName );
    EffectShader * const effect = renderFactory->createEffectShader( effectFilename );
    assert( effect );
    if( NULL == effect ) return & nullToRender_;

    ToRender * const newToRender = new ToRenderImp( node, effect );
    toRenders_.push_back( ToRenderPtr( newToRender ) );

    return newToRender;
}

void MyRenderEventListenerImp::displayReset( int x, int y, int width, int height ) {
    updateCameraProjection( (float) width / (float) height );
}

void MyRenderEventListenerImp::updateCameraProjection( float aspectRatio ) {
    camera_->setAspect( aspectRatio );
    camera_->getProjectionMatrix44( matrixProjection_, bRightHandHardware_, true );
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
}

void MyRenderEventListenerImp::updateCameraView()
{
    camera_->getViewMatrix44( view_, true );
    matrixProjectionView_ = matrixProjection_ * view_;
}

void MyRenderEventListenerImp::updateEffect( float elapsedTime )
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        ToRender * const toRender = (ToRender *) (actor->userData);
        toRender->updateMatrix( actor, view_, matrixProjectionView_ );
    }
}

void MyRenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;

    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify
    {
        render->setRenderState()->setWireframe()->setSolid();
        render->setRenderState()->setCull()->setClockWise();
        MY_FOR_EACH_MOD( ToRenders, iter, toRenders_ )
            (*iter)->display();
    }
    DXUT_EndPerfEvent();

    render->endScene();
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
