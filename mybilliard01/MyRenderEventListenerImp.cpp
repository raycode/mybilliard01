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

    initCamera( CAMERA0, NxVec3( -70.f, 0.f, 45.f ), NxVec3( 1.f, 0.f, -0.3f ) );
    initLight( LIGHT0, NxVec3( -40.f, 0.f, 80.f ), NxVec3( 0.f, -1.f, -2.f ) );
    initSound();
    initPhys();
    initVisualOnlyObjects();
}

void MyRenderEventListenerImp::initCamera( size_t index, NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_[ index ] = MyCameraPtr( new MyCamera( colladaCamera, phys_.get(), this, pos, dir, bRightHandHardware_ ) );
    camera_[ index ]->setMovementToFixedHeight( pos.z );
}

void MyRenderEventListenerImp::initLight( size_t index, NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_[ index ] = MyCameraPtr( new MyCamera( colladaCamera, phys_.get(), this, pos, dir, bRightHandHardware_ ) );
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
    resetEffect( renderFactory );
    scene_->setRenderFactory( renderFactory );
    resetCameraProjection( (float) width / (float) height );
    resetLightProjection( (float) width / (float) height );
    resetEffectProjection();
}

void MyRenderEventListenerImp::resetEffect( RenderBufferFactory * renderFactory )
{
    createShadowMap( renderFactory );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );

        const wstring nodeName = convertString( actor->getName() );
        Node * const node = scene_->getNode( nodeName );

        actor->userData = createEffectFeeder( node, renderFactory );
    }

    createSharedVariableFeeder();
}

void MyRenderEventListenerImp::resetCameraProjection( float aspectRatio ) {
    camera_[ CAMERA0 ]->setAspect( aspectRatio );
    camera_[ CAMERA0 ]->getProjectionMatrix44( matrixProjection_[ CAMERA0 ], bRightHandHardware_, true );
}

void MyRenderEventListenerImp::resetLightProjection( float aspectRatio ) {
    camera_[ LIGHT0 ]->setAspect( aspectRatio );
    camera_[ LIGHT0 ]->getProjectionMatrix44( matrixProjection_[ LIGHT0 ], bRightHandHardware_, true );
}

void MyRenderEventListenerImp::resetEffectProjection()
{
    sharedVaribleFeeder_->updateProjection( matrixProjection_[ CAMERA0 ] );
    shadowFeeder_->updateProjection( matrixProjection_[ LIGHT0 ] );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateProjection( matrixProjection_[ CAMERA0 ] );
    }
}

void MyRenderEventListenerImp::update( RenderBufferFactory * renderFactory, float elapsedTime )
{
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    for( size_t i = 0; i < SIZE_OF_CAMERA_ENUM; ++i )
        updateCamera( i, elapsedTime );
    updateEffect( elapsedTime );
    updateStickPower( elapsedTime );
    updateStickPosition();
    phys_->fetchResult();
}

void MyRenderEventListenerImp::updateCamera( size_t index, float elapsedTime ) {
    camera_[ index ]->update( elapsedTime );
    updateCameraView( index );
    updateCameraPosAndDir( index );
}

void MyRenderEventListenerImp::updateCameraView( size_t index )
{
    camera_[ index ]->getViewMatrix44( matrixView_[ index ], true );
    matrixProjectionView_[ index ] = matrixProjection_[ index ] * matrixView_[ index ];
}

void MyRenderEventListenerImp::updateCameraPosAndDir( size_t index )
{
    const NxExtendedVec3 pos = camera_[ index ]->getPosition();
    cameraPos_[ index ] = NxVec3( (NxReal) pos.x, (NxReal) pos.y, (NxReal) pos.z );
    cameraDir_[ index ] = camera_[ index ]->getDirectionVector();
}

void MyRenderEventListenerImp::updateEffect( float elapsedTime )
{
    sharedVaribleFeeder_->updateMatrix( cameraPos_[ CAMERA0 ], cameraDir_[ CAMERA0 ],
        matrixView_[ CAMERA0 ], matrixProjectionView_[ CAMERA0 ] );
    shadowFeeder_->updateMatrix( cameraPos_[ LIGHT0 ], cameraDir_[ LIGHT0 ],
        matrixView_[ LIGHT0 ], matrixProjectionView_[ LIGHT0 ] );

    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i ) {
        NxActor * const actor = phys_->getActor( i );
        EffectShaderFeeder * const feeder = (EffectShaderFeeder *) (actor->userData);
        feeder->updateMatrix( actor, cameraPos_[ CAMERA0 ], cameraDir_[ CAMERA0 ],
            matrixView_[ CAMERA0 ], matrixProjectionView_[ CAMERA0 ] );
    }

    updateEffectLights();
}

void MyRenderEventListenerImp::updateEffectLights() {
    const float light0_position[] = { -40.f, 0.f, 80.f, 1.f };
    getSharedVariable( L"Light0_Position" )->setFloatArray( light0_position, 4u );
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
    shadowRenderTarget_->display( render, RenderTargetCallBackPtr( new MyShadowDisplayer( shadowFeeder_.get(), actorGroup_[ ACTORS_BALL ] ) ).get() );
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
    return camera_[ CAMERA0 ].get();
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
