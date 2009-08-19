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

    readNodeTranforms( newNode, node );
    readNodeInstanceGeometries( newNode, node );
    readNodeInstanceControllers();
    readNodeInstanceLights();
    readNodeInstanceCameras();

    readNodeChildNodes();
    readNodeInstanceNodes();
}

typedef daeTArray< daeElementRef > daeElement_Array;

void NodeFactoryImp::readNodeTranforms( NodeImp * newNode, domNodeRef node ) {
    MY_FOR_EACH_COLLADA( daeElement, content, node->getContents() ) {
        NodeTransformPtr transform( readNodeTranform( *content ) );
        if( NULL == transform ) continue;
        newNode->appendNodeTransform( *transform );
    }	
}

NodeTransformPtr NodeFactoryImp::readNodeTranform( domElement * content ) {
    const wstring typeName = convertString( content->getTypeName() );
    const NodeTransformType type = NodeTransform::getType( typeName );
    if( ENodeTransformUnknown == type ) return NodeTransformPtr( (NodeTransform *) NULL );

    NodeTransformPtr transform( new NodeTransform() );
    transform->setType( type ); 

    bool rstParse = false;
    switch( type )
    {
    case ENodeTransformRotate:
        rstParse = readNodeTransformRotate( &*transform, content );
        break;
    case ENodeTransformTranslate:
        rstParse = readNodeTransformTranslate( &*transform, content );
        break;
    case ENodeTransformScale:
        rstParse = readNodeTransformScale( &*transform, content );
        break;
    case ENodeTransformLookAt:
        rstParse = readNodeTransformLookAt( &*transform, content );
        break; 
    case ENodeTransformMatrix:
        rstParse = readNodeTransformMatrix( &*transform, content );
        break;

    case ENodeTransformSkew: // not supported
    default:
        break;
    }
    if( false == rstParse ) return NodeTransformPtr( (NodeTransform*) NULL );

    return transform;
}

bool NodeFactoryImp::readNodeTransformRotate( NodeTransform * transform, domElement * content )
{
    domRotateRef rotateArray = daeDowncast< domRotate >( content ) ;
    if( NULL == rotateArray ) return false;

    domFloat4 value = rotateArray->getValue();
    if( value.getCount() != 4 ) return false;

    NxVec3 rot;
    rot.x = (NxReal) value[0];
    rot.y = (NxReal) value[1];
    rot.z = (NxReal) value[2];
    const NxReal angle = (NxReal) value[3];

    transform->setRotate( rot, angle );
    transform->setSid( convertString( rotateArray->getSid() ) );
    return true;
}

bool NodeFactoryImp::readNodeTransformTranslate( NodeTransform * transform, domElement * content )
{
    domTranslateRef translateArray = daeDowncast< domTranslate >( content );
    if( NULL == translateArray ) return false;

    domFloat3 value = translateArray->getValue();
    if( value.getCount() != 3 ) return false;

    // get the transation data 
    NxVec3 trans;
    trans.x = (NxReal) value[0];
    trans.y = (NxReal) value[1];
    trans.z = (NxReal) value[2];			

    transform->setTranslate( trans ); 
    transform->setSid( convertString( translateArray->getSid() ) ); 
    return true;
}

bool NodeFactoryImp::readNodeTransformScale( NodeTransform * transform, domElement * content )
{
    domScaleRef scaleArray = daeDowncast< domScale >( content );
    if( NULL == scaleArray ) return false;

    domFloat3 value = scaleArray->getValue();
    if( value.getCount() != 3 ) return false; 

    NxVec3 scale;
    scale.x = (NxReal) value[0];
    scale.y = (NxReal) value[1];
    scale.z = (NxReal) value[2];

    transform->setScale( scale ); 
    transform->setSid( convertString( scaleArray->getSid() ) ); 
    return true;
}

bool NodeFactoryImp::readNodeTransformLookAt( NodeTransform * transform, domElement * content )
{
    // load rotation
    domLookatRef lookatArray = daeDowncast< domLookat >( content );
    if( NULL == lookatArray ) return false;

    domFloat3x3 value = lookatArray->getValue();
    if( value.getCount() != 9) return false; 

    NxVec3 lookAt[3];
    lookAt[0].x = (NxReal) value[0];
    lookAt[0].y = (NxReal) value[1];
    lookAt[0].z = (NxReal) value[2];

    lookAt[1].x = (NxReal) value[3];
    lookAt[1].y = (NxReal) value[4];
    lookAt[1].z = (NxReal) value[5];

    lookAt[2].x = (NxReal) value[6];
    lookAt[2].y = (NxReal) value[7];
    lookAt[2].z = (NxReal) value[8];

    transform->setLookAt( lookAt ); 
    transform->setSid( convertString( lookatArray->getSid() ) ); 
    return true;
}

bool NodeFactoryImp::readNodeTransformMatrix( NodeTransform * transform, domElement * content )
{
    // beware, collada spec is column major
    domMatrixRef matrixArray = daeDowncast< domMatrix >( content );
    if( NULL == matrixArray ) return false;

    domListOfFloats value = matrixArray->getValue();
    if( value.getCount() != 16 ) return false;

    NxMat34 mat;
    {
        NxF32 floatMat[ 16 ];
        for( int i = 0; i < 16; ++i )
            floatMat[ i ] = (NxF32) value[ i ];
        mat.setColumnMajor44( floatMat );
    }

    transform->setMatrix( mat );
    transform->setSid( convertString( matrixArray->getSid() ) ); 
    return true;
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