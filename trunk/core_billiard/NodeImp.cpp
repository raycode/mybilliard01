#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


NodeImp::NodeImp()
    : parent_(NULL), nextSibling_( NULL ), firstChildren_( NULL ), nbChildren_( 0 )
    ,needToUpdateLocalMatrix_( true ), needToUpdateLocalToWorldMatrix_( true )
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



void NodeImp::update( float time ) {
    if( false == isNeedToUpdate() ) return;

    updateOrient( time );

    NodeImp * kids = firstChildren_;
    while( kids ) {
        kids->update( time );
        kids = kids->nextSibling_;
    }
}

void NodeImp::display( Render * render ) {
    {
        renderInstanceGeometries( render );
    }
}

void NodeImp::renderInstanceGeometries( Render * render ) {
    MY_FOR_EACH( Instances, igeo, instanceGeometries_ ) {
        Geometry * const geo = renderDowncast< Geometry >( (*igeo)->getResolvedReference() );
        if( NULL == geo ) continue;
        geo->display( render );
    }
}

void NodeImp::updateOrient( float time ) {
    if( time > 0 ) {

    }

    if( needToUpdateLocalMatrix_ ) {
        updateLocalMatrix();
        needToUpdateLocalMatrix_ = false;
    }
}

bool NodeImp::isNeedToUpdate() const {
    return needToUpdateLocalMatrix_ == true || needToUpdateLocalToWorldMatrix_ == true;
}

void NodeImp::updateLocalMatrix() {

}

void NodeImp::appendInstanceGeometry( Instance * instanceGeometry ) {
    instanceGeometries_.push_back( instanceGeometry );
}

}