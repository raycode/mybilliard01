#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


NodeImp::NodeImp()
    : parent_(NULL), nextSibling_( NULL ), firstChildren_( NULL ), nbChildren_( 0 )
{
}

Node * NodeImp::getParent() {
    return parent_;
}

wstring NodeImp::getSID() {
    return sid_;
}

Node * NodeImp::getNextSibling() {
    return nextSibling_;
}

Node * NodeImp::getFirstChild() {
    return firstChildren_;
}

size_t NodeImp::getNbChild() {
    return nbChildren_;
}

void NodeImp::setSID( wstring sid ) {
    sid_ = sid;
}

bool NodeImp::hasParent() {
    return NULL != getParent();
}
bool NodeImp::hasNextSibling() {
    return NULL != getNextSibling();
}
bool NodeImp::hasFirstChild() {
    return NULL != getFirstChild();
}

void NodeImp::setParent( NodeImp * parent ) {
    parent_ = parent;
}

void NodeImp::setNextSibling( NodeImp * nextSibling ) {
    nextSibling_ = nextSibling;
}

void NodeImp::appendChild( NodeImp * child ) {
    if ( NULL == firstChildren_ )
	    firstChildren_ = child; 
    else
    {
	    child->setNextSibling( firstChildren_ ); 
	    firstChildren_ = child; 
    }

    nbChildren_++; 
}

void NodeImp::display() {
    renderInstanceGeometries();

    for( Node * child = getFirstChild(); NULL != child; child = child->getNextSibling() ) 
        child->display();
}

void NodeImp::display_positionOnly() {
    renderInstanceGeometries_positionOnly();

    for( Node * child = getFirstChild(); NULL != child; child = child->getNextSibling() ) 
        child->display_positionOnly();
}

void NodeImp::renderInstanceGeometries() {
    MY_FOR_EACH( Instances, igeo, instanceGeometries_ ) {
        GeometryDisplayable * const geo
            = renderDowncast< GeometryDisplayable >( (*igeo)->getResolvedReference() );
        CONTINUE_UNLESS( geo );
        geo->display();
    }
}

void NodeImp::renderInstanceGeometries_positionOnly() {
    MY_FOR_EACH( Instances, igeo, instanceGeometries_ ) {
        GeometryDisplayable * const geo
            = renderDowncast< GeometryDisplayable >( (*igeo)->getResolvedReference() );
        CONTINUE_UNLESS( geo );
        geo->display_positionOnly();
    }
}

void NodeImp::appendInstanceGeometry( Instance * instanceGeometry ) {
    instanceGeometries_.push_back( instanceGeometry );
}

}