#include "StdAfx.h"
#include "my_app.h"

MyRenderEventListenerImp::MyRenderEventListenerImp( wstring sceneFile, wstring physX_File )
: scene_( new SceneImp() )
, phys_( new MyPhysX() )
, ballContactReport_( this, this )
, bRightHandHardware_( false )
, bPaused_( false )
, cueShotStrength_( 10000000.f )
{
    const bool bScene = scene_->load( sceneFile );
    const bool bPhys = phys_->loadXMLFile( physX_File );
    assert( bScene );
    assert( bPhys );

    initCamera( NxVec3( -70.f, 0.f, 45.f ), NxVec3( 1.f, 0.f, -0.3f ) );
    initSound();
    initPhys();
}

void MyRenderEventListenerImp::initCamera( NxVec3 pos, NxVec3 dir ) {
    Camera * const colladaCamera = scene_->getCameraByIndex( 0u );
    camera_ = MyCameraPtr( new MyCamera( colladaCamera, phys_.get(), pos, dir, bRightHandHardware_ ) );
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
    initPhysContactReport();
    for( size_t i = 0; i < phys_->getNumberOfActors(); ++i )
    {
        NxActor * const actor = phys_->getActor( i );
        initPhysActors( actor );
        initPhysActorGroups( actor );
        initPhysMaterial( actor );
    }

    defaultCueBallPos_ = getCueBall()->getGlobalPosition();
}

void MyRenderEventListenerImp::initPhysContactReport()
{
    phys_->getScene()->setActorGroupPairFlags(0,0, ballContactReport_.getContactReportFlags() );
    phys_->getScene()->setUserContactReport( & ballContactReport_ );
}

void MyRenderEventListenerImp::initPhysActors( NxActor * actor )
{
    const wstring name = convertString( actor->getName() );
    if( name == L"CUE_BALL" ) actors_[ ACTOR_CUE_BALL ] = actor;
    else if( name == L"cue_stick" ) actors_[ ACTOR_STICK ] = actor;
}

void MyRenderEventListenerImp::initPhysActorGroups( NxActor * actor )
{
    const wstring name = convertString( actor->getName() );
    if( name == L"CUE_BALL" || name.find( L"ball" ) == 0 ) actorGroup_[ ACTORS_BALL ].insert( actor );
    else if( name.find( L"pocket" ) == 0 ) actorGroup_[ ACTORS_POCKET ].insert( actor );
    else if( name.find( L"rail" ) == 0 ) actorGroup_[ ACTORS_RAIL ].insert( actor );
}

void MyRenderEventListenerImp::initPhysMaterial( NxActor * actor )
{
    if( isActorBall( actor ) )
    {
        actor->raiseBodyFlag( NX_BF_FROZEN_POS_Z ); 
        actor->raiseActorFlag( NX_AF_FORCE_CONE_FRICTION ); 
        actor->setAngularDamping( 1.f );
        actor->setLinearDamping( 1.f );
    }
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
    phys_->simulate( bPaused_ ? 0.f : elapsedTime );
    updateCamera( elapsedTime );
    updateEffect( elapsedTime );
    updateStickPosition();
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
    const NxExtendedVec3 cameraPos = getMyCamera()->getPosition();
    NxVec3 newStickPosition( (NxReal) cameraPos.x, (NxReal) cameraPos.y, (NxReal) cameraPos.z );
    newStickPosition += getMyCamera()->getRightVector() * 10.f;
    getStick()->moveGlobalPosition( newStickPosition );

    NxVec3 right = getMyCamera()->getRightVector();
    NxVec3 up = getMyCamera()->getUpVector();
    NxVec3 dir = getMyCamera()->getDirectionVector();
    getStick()->moveGlobalOrientation( NxMat33( right, up, dir ) );
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

NxVec3 MyRenderEventListenerImp::getBallPosition() {
    return getCueBall()->getGlobalPosition();
}

NxActor * MyRenderEventListenerImp::getCueBall() {
    return actors_[ ACTOR_CUE_BALL ];
}
NxActor * MyRenderEventListenerImp::getStick() {
    return actors_[ ACTOR_STICK ];
}

void MyRenderEventListenerImp::shotCueBall() {
    NxVec3 dir = getMyCamera()->getDirectionVector();
    dir.z = 0.f;
    getCueBall()->addForce( dir * cueShotStrength_ );
}

void MyRenderEventListenerImp::bringCueBallBack() {
    getCueBall()->setGlobalPosition( defaultCueBallPos_ );

    NxMat33 identity;
    identity.id();
    getCueBall()->setGlobalOrientation( identity );

    NxVec3 zero;
    zero.zero();
    getCueBall()->setLinearVelocity( zero );
}

void MyRenderEventListenerImp::pause( bool bPause ) {
    bPaused_ = bPause;
}

bool MyRenderEventListenerImp::isPaused() {
    return bPaused_;
}
