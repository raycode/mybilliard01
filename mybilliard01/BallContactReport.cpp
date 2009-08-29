#include "Stdafx.h"
#include "my_app.h"


BallContactReport::BallContactReport( SoundRetriever * sound, ActorRecognizer * actorRecognizer )
: sound_( sound )
, actorRecognizer_( actorRecognizer )
, numberOfSamples_BallBounce_( 0u )
, averageForce_BallBounce_ ( 0.f )
{
}

NxContactPairFlag BallContactReport::getContactReportFlags()
{
    return ( NxContactPairFlag )(
        NX_NOTIFY_FORCES |
        NX_NOTIFY_ON_END_TOUCH |
        NX_NOTIFY_ON_START_TOUCH |
        NX_NOTIFY_ON_TOUCH
    );
}

void BallContactReport::onContactNotify(NxContactPair& pair, NxU32 events)
{
    switch( events )
    {
    case NX_NOTIFY_ON_START_TOUCH:
        onContactStart( pair );
        break;
    case NX_NOTIFY_ON_END_TOUCH:
        onContactEnd( pair );
        break;
    case NX_NOTIFY_ON_TOUCH:
        onContactTouch( pair );
        break;
    default:
        OutputDebugStr( (wstring(L"UserContactReport: ") + DebugHelper::getStringFromInt(events) + L"\n").c_str() );
        break;
    }
}

void BallContactReport::onContactStart( NxContactPair & pair )
{
    for( size_t i = 0; i < 2; ++i ) if( pair.isDeletedActor[ i ] ) return;

    playSound_BallBounce( pair );
    playSound_Pocket( pair );
    playSound_Bump( pair );
}

void BallContactReport::onContactTouch( NxContactPair & pair )
{
}

void BallContactReport::onContactEnd( NxContactPair & pair )
{
}

void BallContactReport::playSound_BallBounce( NxContactPair & pair )
{
    for( size_t i = 0; i < 2; ++i ) if( false == actorRecognizer_->isActorBall( pair.actors[ i ] ) ) return;

    const float strength = pair.sumFrictionForce.magnitude();
    averageForce_BallBounce_ += strength / ( numberOfSamples_BallBounce_ + 1 );
    numberOfSamples_BallBounce_ = std::min( numberOfSamples_BallBounce_ + 1, numeric_limits< size_t >::max() - 1 );

    if( 1 == numberOfSamples_BallBounce_ ) {
        sound_->getRandomSound( SoundRetriever::SOUND_BREAK )->playSound();
    } else
    {
        const bool bStrong = (strength >= averageForce_BallBounce_);
        sound_->getRandomSound( bStrong ? SoundRetriever::SOUND_BALL_STRONG : SoundRetriever::SOUND_BALL_WEAK )->playSound();
    }
}

void BallContactReport::playSound_Pocket( NxContactPair & pair )
{
    NxActor * const actor0 = pair.actors[ 0 ];
    NxActor * const actor1 = pair.actors[ 1 ];
    const bool bPocket1 = actorRecognizer_->isActorPocket( actor0 ) && actorRecognizer_->isActorBall( actor1 );
    const bool bPocket2 = actorRecognizer_->isActorPocket( actor1 ) && actorRecognizer_->isActorBall( actor0 );
    if( false == bPocket1 && false == bPocket2 ) return;

    sound_->getRandomSound( SoundRetriever::SOUND_POCKET );
}

void BallContactReport::playSound_Bump( NxContactPair & pair )
{
    NxActor * const actor0 = pair.actors[ 0 ];
    NxActor * const actor1 = pair.actors[ 1 ];
    const bool bBump1 = actorRecognizer_->isActorRail( actor0 ) && actorRecognizer_->isActorBall( actor1 );
    const bool bBump2 = actorRecognizer_->isActorRail( actor1 ) && actorRecognizer_->isActorBall( actor0 );
    if( false == bBump1 && false == bBump2 ) return;

    sound_->getRandomSound( SoundRetriever::SOUND_BUMP );
}

