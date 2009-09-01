#include "Stdafx.h"
#include "my_app.h"


MyShadowCallBack::MyShadowCallBack( GlobalEffectShaderFeeder * feeder, const ActorGroup * actors, const NodeMap * nodeMap )
: feeder_( feeder )
, actors_( actors )
, nodeMap_( nodeMap )
{
}

void MyShadowCallBack::display( Render * render )
{
    render->clear_Color_Z( PixelColor( 0.f, 0.f, 0.f, 0.f ), 1.f );
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setClockWise();

    MY_FOR_EACH( set< NxActor * >, iter, *actors_ )
    {
        NxActor * const actor = *iter;
        currentNode_ = nodeMap_->find( actor )->second;
        assert( currentNode_ );
        feeder_->display( actor );
    }
}

void MyShadowCallBack::displayPass( size_t pass )
{
    currentNode_->display_positionOnly();
}

