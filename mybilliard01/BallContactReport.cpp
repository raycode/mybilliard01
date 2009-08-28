#include "Stdafx.h"
#include "my_app.h"


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

void BallContactReport::onContactEnd( NxContactPair & pair )
{
}

bool BallContactReport::isActorBall( NxActor * actor )
{
    const wstring name = convertString( actor->getName() );
    if( name == L"CUE_BALL" ) return true;
    if( name.find( L"ball" ) == 0 ) return true;
    return false;
}

void BallContactReport::onContactTouch( NxContactPair & pair )
{
}

void BallContactReport::onContactStart( NxContactPair & pair )
{
}