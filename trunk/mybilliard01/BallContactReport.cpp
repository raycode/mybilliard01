#include "Stdafx.h"
#include "my_app.h"


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
    }
}

void BallContactReport::onContactStart( NxContactPair & pair )
{
    for( size_t i = 0; i < 2; ++i )
    {
        if( pair.isDeletedActor[ i ] ) continue;
        NxActor * const actor = pair.actors[ i ];
        const wstring name = convertString( actor->getName() );
        if( name != L"CUE_BALL" && name.find( L"ball" ) != 0 ) continue;

        angularVectors_.insert( AngularVectors::value_type( actor, actor->getAngularVelocity() ) );

        NxVec3 zeroVelocity;
        zeroVelocity.zero();
        //actor->setAngularVelocity( zeroVelocity );
    }

}

void BallContactReport::onContactEnd( NxContactPair & pair )
{
    for( size_t i = 0; i < 2; ++i )
    {
        NxActor * const actor = pair.actors[ i ];
        if( pair.isDeletedActor[ i ] ) continue;
        const wstring name = convertString( actor->getName() );
        if( name != L"CUE_BALL" && name.find( L"ball" ) != 0 ) continue;

        AngularVectors::iterator iter = angularVectors_.find( actor );
        if( iter == angularVectors_.end() ) continue;

        actor->setAngularVelocity( iter->second );

        angularVectors_.erase( iter );
    }

}

void BallContactReport::onContactTouch( NxContactPair & pair )
{

}
