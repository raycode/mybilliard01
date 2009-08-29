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

    playSoundForBallBounce( pair );
}

void BallContactReport::onContactTouch( NxContactPair & pair )
{
}

void BallContactReport::onContactEnd( NxContactPair & pair )
{
}

void BallContactReport::playSoundForBallBounce( NxContactPair & pair )
{
    for( size_t i = 0; i < 2; ++i ) if( false == actorRecognizer_->isActorBall( pair.actors[ i ] ) ) return;

    const float strength = pair.sumFrictionForce.magnitude();
    averageForce_BallBounce_ += strength / ( numberOfSamples_BallBounce_ + 1 );
    numberOfSamples_BallBounce_ = std::min( numberOfSamples_BallBounce_ + 1, numeric_limits< size_t >::max() - 1 );

    const bool bStrong = (strength >= averageForce_BallBounce_);
    sound_->getRandomSound( bStrong ? SoundRetriever::SOUND_BALL_STRONG : SoundRetriever::SOUND_BALL_WEAK )->playSound();

}
