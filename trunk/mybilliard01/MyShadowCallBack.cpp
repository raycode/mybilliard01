#include "Stdafx.h"
#include "my_app.h"


MyShadowCallBack::MyShadowCallBack( GlobalEffectShaderFeeder * feeder, const NodeMap * nodeMap )
: feeder_( feeder )
, nodeMap_( nodeMap )
{
}

void MyShadowCallBack::displayOnRenderTargetCallBack( Render * render )
{
    render->clear_Color_Z( PixelColor( 0.f, 0.f, 0.f, 0.f ), 1.f );
    render->setRenderState()->setWireframe()->setSolid();
    render->setRenderState()->setCull()->setClockWise();

    MY_FOR_EACH( NodeMap, iter, *nodeMap_ )
    {
        currentNode_ = iter->second;

        RowMajorMatrix44f matWorld;
        iter->first->getGlobalPose().getRowMajor44( matWorld );

        feeder_->displayWithEffect( matWorld );
    }
}

void MyShadowCallBack::displayPass( size_t pass ) {
    currentNode_->display_positionOnly();
}

