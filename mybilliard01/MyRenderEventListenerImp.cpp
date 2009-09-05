#include "StdAfx.h"
#include "my_app.h"

MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX( NxVec3(0.0f, 0.0f, -9.81f ) ) )
, ballContactReport_( this, this )
, bPaused_( false )
, cueShotStrength_( 20000000.f * 1.f )
, bChargingStickPower_( false )
, chargedStickPower_( 0.f )
, activeCamera_( CAMERA_0 )
{
    const bool bScene = scene_->load( sceneFile );
    const bool bPhys = phys_->loadXMLFile( physX_File );
    THROW_UNLESS( bScene, exception() );
    THROW_UNLESS( bPhys, exception() );

    initCamera( CAMERA_0, NxVec3( -70.f, 0.f, 45.f ), NxVec3( 1.f, 0.f, -0.3f ) );
    initPhys();
}

void MyRenderEventListenerImp::init()
{
    //initLight( LIGHT0, 80.f, 200.f, NxVec3( -13.f, 10.f, 140.f ), NxVec3( 0.f, -0.090536f, -0.995893f ) );
    initSound();
    initVisualOnlyObjects();
}

void MyRenderEventListenerImp::initCamera( size_t index, NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    cameras_[ index ] = new MyCamera( colladaCamera, false, phys_.get(), this, pos, dir );
    cameras_[ index ]->setMovementToFixedHeight( pos.z );
    cameraMatrixEffects_.push_back( MyCameraPtr( cameras_[ index ] ) );
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

        if( name == ConstString::name_CueBall() ) actors_[ ACTOR_CUE_BALL ] = actor;
        else if( name == ConstString::name_Rack() ) actors_[ ACTOR_RACK ] = actor;
    }
}

void MyRenderEventListenerImp::initPhysActorGroups()
{
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );
        const wstring name = convertString( actor->getName() );

        if( name == ConstString::name_CueBall() ||
            name.find( ConstString::name_Ball_prefix() ) == 0 ) actorGroup_[ ACTORS_BALL ].insert( actor );

        else if( name.find( ConstString::name_Pocket_prefix() ) == 0 )
            actorGroup_[ ACTORS_POCKET ].insert( actor );

        else if( name.find( ConstString::name_Rail_prefix() ) == 0 )
            actorGroup_[ ACTORS_RAIL ].insert( actor );
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
    visualOnlyObjects_[ VISUAL_STICK ] = scene_->getNode( ConstString::name_CueStick() );
    visualOnlyObjects_[ VISUAL_BACKGROUND ] = scene_->getNode( ConstString::name_Background() );
}

void MyRenderEventListenerImp::display( Render * render ) {
    if( false == render->beginScene() ) return;
    DXUT_BeginPerfEvent( DXUT_PERFEVENTCOLOR, L"begin Scene" ); // These events are to help PIX identify

    getActiveCamera()->displayOnRenderTargetCallBack( render );

    DXUT_EndPerfEvent();
    render->endScene();
}   

void MyRenderEventListenerImp::displayLost() {
    sharedVariables_.clear();
    sharedFeeders_.clear();
    feeders_.clear();
}

void MyRenderEventListenerImp::destroy() 
{
}

MyCamera * MyRenderEventListenerImp::getActiveCamera() {
    return cameras_[ activeCamera_ ];
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

bool MyRenderEventListenerImp::isActorBall( NxActor * actor ) {
    return actorGroup_[ ACTORS_BALL ].find( actor ) != actorGroup_[ ACTORS_BALL ].end();
}
bool MyRenderEventListenerImp::isActorPocket( NxActor * actor ) {
    return actorGroup_[ ACTORS_POCKET ].find( actor ) != actorGroup_[ ACTORS_POCKET ].end();
}
bool MyRenderEventListenerImp::isActorRail( NxActor * actor ) {
    return actorGroup_[ ACTORS_RAIL ].find( actor ) != actorGroup_[ ACTORS_RAIL ].end();
}


