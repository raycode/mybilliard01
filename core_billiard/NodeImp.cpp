#include "my_render_imp.h"
namespace my_render_imp {


Node * NodeImp::getParent() {
    return parent_;
}

wstring NodeImp::getID() {
    return id_;
}

wstring NodeImp::getSID() {
    return sid_;
}

wstring NodeImp::getName() {
    return name_;
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

void NodeImp::setID( wstring id ) {
    id_ = id;
}

void NodeImp::setSID( wstring sid ) {
    sid_ = sid;
}

void NodeImp::setName( wstring name ) {
    name_ = name;
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

void NodeImp::render( Render * render ) {
    {
        RenderMatrix matrix( render );
        renderInstanceGeometries( render );
    }

    if( firstChildren_ )
        firstChildren_->render( render );
    if( nextSibling_ )
        nextSibling_->render( render );
}

void NodeImp::renderInstanceGeometries( Render * render ) {
    MY_FOR_EACH( Instances, iter, instanceGeometries_ ) {
        Instance * const igeo = *iter;
        Geometry * const geo = renderDowncast< Geometry >( igeo->getResolvedReferrence() );
        geo->draw( render );
    }
}

NodeImp::NodeImp()
: parent_(NULL), nextSibling_( NULL ), firstChildren_( NULL ), nbChildren_( 0 )
,needToUpdateLocalMatrix_( true ), needToUpdateLocalToWorldMatrix_( true )
{
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