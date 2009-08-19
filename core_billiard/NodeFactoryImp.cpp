#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


NodeFactoryImp::NodeFactoryImp( InstanceResolver * instanceResolver )
    : instanceResolver_( instanceResolver )
{
}

Node * NodeFactoryImp::createVisualScene( domVisual_sceneRef scene ) {
    const wstring id = convertString( scene->getId() );
    const wstring name = convertString( scene->getName() );
    if( isAlreadyCreated( id ) ) return NULL;

    NodeImp * const newVisualScene = createNode( id, name, L"", NULL );
    if( NULL == newVisualScene ) return NULL;

    MY_FOR_EACH_COLLADA( domNode, nodes, scene->getNode_array() )
        readNode( newVisualScene, *nodes );

    return newVisualScene;
}

NodeImp * NodeFactoryImp::createNode( wstring id, wstring name, wstring sid, NodeImp * parent ) {
    if( isAlreadyCreated( id ) ) return NULL;

    NodeImp * const newNode = new NodeImp();
    if( NULL == newNode ) return NULL;

    nodes_.push_back( NodeImpPtr( newNode ) );

    newNode->setID( id );
    newNode->setName( name );
    newNode->setSID( sid );
    newNode->setParent( parent );

    return newNode;
}

bool NodeFactoryImp::isAlreadyCreated( wstring id ) {
    return NULL != find( id );
}

bool NodeFactoryImp::destroyNode( Node * ptr ) {
    MY_FOR_EACH( Nodes, iter, nodes_ ) {
        if( (&**iter) != ptr ) continue;
        nodes_.erase( iter );
        return true;
    }
    return false;
}

Node * NodeFactoryImp::find( wstring id ) {
    return findNode( id );
}

NodeImp * NodeFactoryImp::findNode( wstring id ) {
    MY_FOR_EACH( Nodes, iter, nodes_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

void NodeFactoryImp::readNode( NodeImp * parentNode, domNodeRef node )
{
    const wstring id = convertString( node->getId() );
    const wstring name = convertString( node->getName() );
    const wstring sid = convertString( node->getSid() );

    if( isAlreadyCreated( id ) ) {
        parentNode->appendChild( findNode( id ) );
        return;
    }

    NodeImp * const newNode = createNode( id, name, sid, parentNode );
    parentNode->appendChild( newNode ); 

    readNodeInstanceGeometries( newNode, node );
    readNodeInstanceControllers();
    readNodeInstanceLights();
    readNodeInstanceCameras();

    readNodeChildNodes();
    readNodeInstanceNodes();
}

void NodeFactoryImp::readNodeInstanceGeometries( NodeImp * newNode, domNodeRef node ) {
    MY_FOR_EACH_COLLADA( domInstance_geometry, igeo, node->getInstance_geometry_array() ) {
        const wstring url = convertString( (*igeo)->getUrl().originalStr() );
        Instance * const instance = instanceResolver_->createInstance( url );
        if( NULL == instance ) continue;

        newNode->appendInstanceGeometry( instance );
    }
}

void NodeFactoryImp::readNodeChildNodes() {
    // TODO
}

void NodeFactoryImp::readNodeInstanceNodes() {
    // TODO
}

void NodeFactoryImp::readNodeInstanceControllers() {
    // TODO
}

void NodeFactoryImp::readNodeInstanceLights() {
    // TODO
}

void NodeFactoryImp::readNodeInstanceCameras() {
    // TODO
}

}