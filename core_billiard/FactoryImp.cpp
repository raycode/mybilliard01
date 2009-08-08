#include "my_render_imp.h"
namespace my_render_imp {

Base * FactoryImp::resolveInstanceUrl( wstring url )
{
#define IF_FIND_RETURN( FACTORY, URL ) { Base * base = FACTORY->find( URL ); if( base ) return base; }
    IF_FIND_RETURN( nodeFactory_, url );
    IF_FIND_RETURN( geometryFactory_, url );
#undef IF_FIND_RETURN

    return NULL;
}

FactoryImp::FactoryImp()
: nodeFactory_( new NodeFactoryImp( this ) )
, geometryFactory_( new GeometryFactoryImp( this ) )
{
}

Node * FactoryImp::createVisualScene( domVisual_sceneRef vscene ) {
    Node * const found = nodeFactory_->find( convertString( vscene->getId() ) );
    if( found ) return NULL;

    return nodeFactory_->createVisualScene( vscene );
}

Geometry * FactoryImp::createGeometry( domGeometryRef geo ) {
    Geometry * const found = geometryFactory_->find( convertString( geo->getId() ) );
    if( found ) return NULL;

    return geometryFactory_->createGeometry( geo );
}

void FactoryImp::release( Base * obj ) {
    if( NULL == obj ) return;

    nodeFactory_->release( renderDowncast< Node >( obj ) );
    geometryFactory_->release( renderDowncast< Geometry >( obj ) );
}

Instance * FactoryImp::createInstance( wstring url, Base * owner ) {
    InstanceImp * const instance = new InstanceImp( this );
    instance->setUrl( url );
    instance->setInstanceOwner( owner );
    instances_.push_back( InstanceImpPtr( instance ) );
    return instance;
}

void FactoryImp::releaseInstance( Instance * ptr ) {
    MY_FOR_EACH( Instances, iter, instances_ ) {
        if( &**iter != ptr ) continue;

        instances_.erase( iter );
        break;
    }
}



}
