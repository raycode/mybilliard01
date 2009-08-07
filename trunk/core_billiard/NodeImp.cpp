#include "my_render_imp.h"
namespace my_render_imp {


Node * NodeImp::getParent() {
    return parent_;
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

void NodeImp::update( float time ) {
    if( false == isNeedToUpdate() ) return;

    updateOrient( time );

    NodeImp * kids = firstChildren_;
    while( kids ) {
        kids->update( time );
        kids = kids->nextSibling_;
    }
}

void NodeImp::render( RenderImp * render ) const {
    {
        RenderImp::MatrixStackPtr matrix = render->createMatrix();

        InstanceGeometriesIterator iter = instanceGeometries_.begin();
        for( ; iter != instanceGeometries_.end(); ++iter ) {
            InstanceGeometry * const instanceGeometry = *iter;
            Geometry * const geometry = instanceGeometry->getGeometry();
            geometry->draw( render );
        }
    }

    if( firstChildren_ )
        firstChildren_->render( render );
    if( nextSibling_ )
        nextSibling_->render( render );
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

}