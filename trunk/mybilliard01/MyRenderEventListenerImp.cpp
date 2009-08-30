#include "StdAfx.h"
#include "my_app.h"

MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX( NxVec3(0.0f, 0.0f, -9.81f ) ) )
, ballContactReport_( this, this )
, bRightHandHardware_( false )
, bPaused_( false )
, cueShotStrength_( 20000000.f * 1.f )
, bChargingStickPower_( false )
, chargedStickPower_( 0.f )
{
    const bool bScene = scene_->load( sceneFile );
    const bool bPhys = phys_->loadXMLFile( physX_File );
    assert( bScene );
    assert( bPhys );

    initCamera( NxVec3( -70.f, 0.f, 45.f ), NxVec3( 1.f, 0.f, -0.3f ) );
    initSound();
    initPhys();
    initVisualOnlyObjects();
}

void MyRenderEventListenerImp::initCamera( NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, phys_.get(), this, pos, dir, bRightHandHardware_ ) );
    camera_->setMovementToFixedHeight( pos.z );
}

bool MyRenderEventListenerImp::isActorBall( NxActor * actor ) {
    return actorGroup_[ ACTORS_BALL ].find( actor ) != actorGroup_[ ACTORS_BALL ].end();
}
bool MyRenderEventListenerImp::isActorPocket( NxActor * actor ) {
    return actorGroup_[ ACTORS_POCKET ].find( actor ) != actorGroup_[ ACTORS_POCKET ].end();
}
bool MyRenderEventListenerImp::isActorRail( NxActor * actor ) {
    return actorGroup_[ ACTORS_RAIL ].find( actor ) != actorGroup_[ ACTORS_RAIL ].end();
}

void MyRenderEventListenerImp::initSound()
{
#define LOAD_SOUND_HANLDE( WHICH_SOUND, WHICH_METHOD ) \
    for( size_t i = 0; i < 30; ++i ) { const wstring filename = ConstString::WHICH_METHOD( i + 1 ); if( false == filename.empty() ) loadSound( WHICH_SOUND, filename ); }

    LOAD_SOUND_HANLDE( SOUND_BALL_STRONG, soundFilename_BallStrong );
    LOAD_SOUND_HANLDE( SOUND_BALL_WEAK, soundFilename_BallWeak );
    LOAD_SOUND_HANLDE( SOUND_BREAK, soundFilename_BallBreak );
    LOAD_SOUND_HANLDE( SOUND_CHALK, soundFilename_Chalk );
    LOAD_SOUND_HANLDE( SOUND_POCKET, soundFilename_Pocket );
    LOAD_SOUND_HANLDE( SOUND_CUE_STRONG, soundFilename_CueStrong );
    LOAD_SOUND_HANLDE( SOUND_CUE_WEAK, soundFilename_CueWeak );
    LOAD_SOUND_HANLDE( SOUND_BUMP, soundFilename_BounceOnRail );

#undef LOAD_SOUND_HANLDE
}

bool MyRenderEventListenerImp::loadSound( int soundType, wstring filename )
{
    SoundHandlePtr newSound = SoundHandlePtr( openAL_.createSoundHandle( filename ), MyOpenAL::Destroyer( &openAL_ ) );
    assert( NULL != newSound );
    if( NULL == newSound ) return false;

    sounds_[ soundType ].push_back( newSound );
    return true;
}

void MyRenderEventListenerImp::initPhys()
{
    initPhysUserCallBacks();
    initPhysMainActors();
    initPhysActorGroups();
    initPhysBalls();
}

void MyRenderEventListenerImp::initPhysUserCallBacks() {
    phys_->setContactReportCallBack( & ballContactReport_ );
}

void MyRenderEventListenerImp::initPhysMainActors()
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );

        if( name == L"CUE_BALL" ) actors_[ ACTOR_CUE_BALL ] = actor;
        else if( name == L"rack01" ) actors_[ ACTOR_RACK ] = actor;
    }
}

void MyRenderEventListenerImp::initPhysActorGroups()
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );

        if( name == L"CUE_BALL" || name.find( L"ball" ) == 0 ) actorGroup_[ ACTORS_BALL ].insert( actor );
        else if( name.find( L"pocket" ) == 0 ) actorGroup_[ ACTORS_POCKET ].insert( actor );
        else if( name.find( L"rail" ) == 0 ) actorGroup_[ ACTORS_RAIL ].insert( actor );
    }
}

void MyRenderEventListenerImp::initPhysBalls()
{
    MY_FOR_EACH( ActorGroup, ball, actorGroup_[ ACTORS_BALL ] )
    {
        initPhysBallMaterial( *ball );
        initPhysBallCCD( *ball );
        initPhysBallPosition( *ball );
    }
}

void MyRenderEventListenerImp::initPhysBallMaterial( NxActor * actor )
{
    actor->raiseBodyFlag( NX_BF_FROZEN_POS_Z ); 
    actor->raiseActorFlag( NX_AF_FORCE_CONE_FRICTION ); 
    actor->setAngularDamping( 1.f );
    actor->setLinearDamping( 1.f );
    actor->putToSleep();
}

void MyRenderEventListenerImp::initPhysBallCCD( NxActor * actor )
{
    actor->setCCDMotionThreshold( 2.f );
    phys_->assignCCDSkeleton( actor );
}

void MyRenderEventListenerImp::initPhysBallPosition( NxActor * actor )
{
    ballDefaultPositions_.insert( BallDefaultPositions::value_type( actor, actor->getGlobalPosition() ) );
}

const NxVec3 & MyRenderEventListenerImp::getBallDefaultPosition( NxActor * actor )
{
    BallDefaultPositions::const_iterator iter = ballDefaultPositions_.find( actor );
    if( iter == ballDefaultPositions_.end() ) throw exception();
    return iter->second;
}

void MyRenderEventListenerImp::initVisualOnlyObjects()
{
    visualOnlyObjects_[ VISUAL_STICK ] = scene_->getNode( L"cue_stick" );
    visualOnlyObjects_[ VISUAL_BACKGROUND ] = scene_->getNode( L"background" );
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
    createShadowMap( renderFactory );

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
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    updateCamera( elapsedTime );
    updateEffect( elapsedTime );
    updateStickPosition();
    updateStickPower( elapsedTime );
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

void MyRenderEventListenerImp::updateStickPosition() {
    //const NxExtendedVec3 cameraPos = getActiveCamera()->getPosition();
    //NxVec3 newStickPosition( (NxReal) cameraPos.x, (NxReal) cameraPos.y, (NxReal) cameraPos.z );
    //newStickPosition += getActiveCamera()->getRightVector() * 10.f;
    //getStick()->moveGlobalPosition( newStickPosition );

    //NxVec3 right = getActiveCamera()->getRightVector();
    //NxVec3 up = getActiveCamera()->getUpVector();
    //NxVec3 dir = getActiveCamera()->getDirectionVector();
    //getStick()->moveGlobalOrientation( NxMat33( right, up, dir ) );
}

void MyRenderEventListenerImp::updateStickPower( float elapsedTime ) {
    if( bChargingStickPower_ ) chargedStickPower_ = std::min( elapsedTime + chargedStickPower_, 100.f );
}

SoundHandle * MyRenderEventListenerImp::getRandomSound( int soundType )
{
    uniform_int<int> unif( 0, sounds_[ soundType ].size() -1 );
    const size_t index = unif( eng_ );
    return sounds_[ soundType ].at( index ).get();
}

void MyRenderEventListenerImp::display( Render * render ) {
    render->clear_Color_Z( PixelColor( 0, 45, 50, 170 ), 1.0f );
    if( false == render->beginScene() ) return;
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify

    preDisplay( render );
    onDisplay( render );
    postDisplay( render );

    DXUT_EndPerfEvent();
    render->endScene();
}   

void MyRenderEventListenerImp::preDisplay( Render * render )
{
    //render->setRenderTarget( shadowMap_.get() );
    //MY_FOR_EACH( EffectShaderFeeders, iter, feeders_ )
    //    (*iter)->display_positionOnly();
    //render->unsetRenderTarget();
}

void MyRenderEventListenerImp::onDisplay( Render * render )
{
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setClockWise();
    MY_FOR_EACH( EffectShaderFeeders, iter, feeders_ )
        (*iter)->display();
}

void MyRenderEventListenerImp::postDisplay( Render * render )
{
}

void MyRenderEventListenerImp::displayLost() {
    sharedVariables_.clear();
    feeders_.clear();
}

void MyRenderEventListenerImp::destroy() 
{
}

MyCamera * MyRenderEventListenerImp::getActiveCamera() {
    return camera_.get();
}

NxVec3 MyRenderEventListenerImp::getCueBallPosition() {
    return getCueBall()->getGlobalPosition();
}

NxActor * MyRenderEventListenerImp::getCueBall() {
    return actors_[ ACTOR_CUE_BALL ];
}

void MyRenderEventListenerImp::readyToHitCueBall() {
    bChargingStickPower_ = true;
}

float MyRenderEventListenerImp::getHowMuchPowerIsCharged() {
    return chargedStickPower_;
}

void MyRenderEventListenerImp::hitCueBall() {
    NxVec3 dir = getActiveCamera()->getDirectionVector();
    dir.z = 0.f;
    getCueBall()->addForce( dir * cueShotStrength_ * chargedStickPower_ );

    bChargingStickPower_ = false;
    chargedStickPower_ = 0.f;
}

void MyRenderEventListenerImp::resetBall( NxActor * ball )
{
    NxMat33 identity;
    identity.id();

    NxVec3 zero;
    zero.zero();

    ball->setGlobalPosition( getBallDefaultPosition( ball ) );
    ball->setGlobalOrientation( identity );
    ball->setLinearVelocity( zero );

    initPhysBallMaterial( ball );
}

void MyRenderEventListenerImp::bringCueBallBack() {
    resetBall( getCueBall() );
}

void MyRenderEventListenerImp::restart()
{
    MY_FOR_EACH( BallDefaultPositions, iter, ballDefaultPositions_ )
        resetBall( iter->first );
}

void MyRenderEventListenerImp::pause( bool bPause ) {
    bPaused_ = bPause;
}

bool MyRenderEventListenerImp::isPaused() {
    return bPaused_;
}

bool MyRenderEventListenerImp::isBallMoving() {
    MY_FOR_EACH( ActorGroup, iter, actorGroup_[ ACTORS_BALL ] ) {
        NxActor * const actor = *iter;
        if( actor->getLinearVelocity().magnitude() >= 50.f )
            return true;
    }
    return false;
}
