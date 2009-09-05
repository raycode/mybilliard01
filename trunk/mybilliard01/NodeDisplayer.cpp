#include "stdafx.h"
#include "my_app.h"


NodeDisplayer::NodeDisplayer( Node * node, bool bPositionOnly )
: node_( node )
, bPositionOnly_( bPositionOnly )
{
}

void NodeDisplayer::displayPass( size_t pass )
{
    if( bPositionOnly_ )
        node_->display_positionOnly();
    else 
        node_->display();
}

