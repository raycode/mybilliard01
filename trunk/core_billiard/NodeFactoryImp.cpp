#include "my_render_imp.h"
namespace my_render_imp {

void NodeFactoryImp::release( Node * ptr ) {
    if( NULL == ptr ) return;

    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (&**iter) != ptr ) continue;

        createdObjects_.erase( iter );
        break;
    }
}

Node * NodeFactoryImp::find( wstring id ) {
    MY_FOR_EACH( CreatedObjects, iter, createdObjects_ ) {
        if( (*iter)->getID() != id ) continue;
        return &**iter;
    }
    return NULL;
}

NodeFactoryImp::NodeFactoryImp( InstanceResolver * instanceResolver )
: instanceResolver_( instanceResolver )
{
}

NodeImp * NodeFactoryImp::createNode( string id, string name, string sid, NodeImp * parent ) {
    if( NULL != find( convertString( id ) ) ) return NULL;

    NodeImp * const newNode = new NodeImp();
    if( NULL == newNode ) return NULL;
    createdObjects_.push_back( NodeImpPtr( newNode ) );

    newNode->setID( convertString( id ) );
    newNode->setName( convertString( name ) );
    newNode->setSID( convertString( sid ) );
    newNode->setParent( parent );

    return newNode;
}

Node * NodeFactoryImp::createVisualScene( domVisual_sceneRef scene ) {
    NodeImp * const rootNode = createNode( scene->getName(), scene->getId(), "", NULL );

    for( size_t i = 0; i < scene->getNode_array().getCount(); ++i ) {
        domNodeRef nodes = scene->getNode_array()[ i ];
        if( NULL == nodes ) continue;

        readNode( nodes, rootNode );
    }

    return rootNode;
}

void NodeFactoryImp::readNode( domNodeRef node, NodeImp * parentNode )
{
    Base * const alreadyExist = find( convertString( node->getId() ) );
    if( NULL != alreadyExist ) {
        NodeImp * const oldNode = renderDowncast< NodeImp >( alreadyExist );
        parentNode->appendChild( oldNode );
        return;
    }

    NodeImp * const newNode = createNode( node->getId(), node->getName(), node->getSid(), parentNode );
    parentNode->appendChild( newNode ); 

    readNodeTranforms( newNode, node );
    readNodeInstanceGeometries( newNode, node );
    readNodeInstanceControllers();
    readNodeInstanceLights();
    readNodeInstanceCameras();

    readNodeChildNodes();
    readNodeInstanceNodes();
}

void NodeFactoryImp::readNodeTranforms( NodeImp * newNode, domNodeRef node ) {
	for ( size_t i = 0; i < node->getContents().getCount(); ++i )
	{
        // TODO
    }
}

void NodeFactoryImp::readNodeInstanceGeometries( NodeImp * newNode, domNodeRef node ) {
    domInstance_geometry_Array igeos = node->getInstance_geometry_array();
    for (size_t i = 0; i < igeos.getCount(); ++i )
    {
        const wstring url = convertString( igeos[i]->getUrl().originalStr() );
        Instance * const instance = instanceResolver_->createInstance( url, newNode );
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