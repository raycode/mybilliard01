#include "Stdafx.h"
#include "my_app.h"


MyShadowDisplayer::MyShadowDisplayer( GlobalEffectShaderFeeder * feeder, const set< NxActor * > & nodes )
: feeder_( feeder )
, nodes_( nodes )
{
}

void MyShadowDisplayer::display( Render * render )
{
    render->clear_Color_Z( PixelColor( 0.f, 0.f, 0.f, 0.f ), 1.f );

    MY_FOR_EACH( set< NxActor * >, iter, nodes_ ) {
        currentNode_ = (Node*) ((*iter)->userData);
        feeder_->display( *iter );
    }
}

void MyShadowDisplayer::displayPass( size_t pass )
{
    currentNode_->display_positionOnly();
}

