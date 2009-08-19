#include "stdafx.h"
#include "my_render_imp.h"
namespace my_render_imp {


ColladaFactoryImp::ColladaFactoryImp()
: nodeFactory_( new NodeFactoryImp( this ) )
, geometryFactory_( new GeometryFactoryImp( this ) )
{
}

Node * ColladaFactoryImp::createVisualScene( domVisual_sceneRef vscene ) {
    Node * const found = nodeFactory_->find( convertString( vscene->getId() ) );
    if( found ) return NULL;

    return nodeFactory_->createVisualScene( vscene );
}

Geometry * ColladaFactoryImp::createGeometry( domGeometryRef geo ) {
    Geometry * const found = geometryFactory_->find( convertString( geo->getId() ) );
    if( found ) return NULL;

    return geometryFactory_->createGeometry( geo );
}

bool ColladaFactoryImp::destroy( Base * obj ) {
    if( NULL == obj ) return false;

    if( nodeFactory_->destroyNode( renderDowncast< Node >( obj ) ) ) return true;
    if( geometryFactory_->destroyGeometry( renderDowncast< Geometry >( obj ) ) ) return true;
    return false;
}

Instance * ColladaFactoryImp::createInstance( wstring url ) {
    InstanceImp * const instance = new InstanceImp( this, url );
    instances_.push_back( InstanceImpPtr( instance ) );
    return instance;
}

bool ColladaFactoryImp::destroyInstance( Instance * ptr ) {
    MY_FOR_EACH( Instances, iter, instances_ ) {
        if( &**iter != ptr ) continue;
        instances_.erase( iter );
        return true;
    }
    return false;
}

wstring ColladaFactoryImp::refineURL( wstring url ) {
    if( false == url.empty() && *(url.begin()) == '#' ) return (url.c_str() + 1);
    return url;
}

Base * ColladaFactoryImp::resolveInstanceURL( wstring url )
{
    const wstring refinedURL = refineURL( url );
#define IF_FIND_RETURN( FACTORY, URL ) { Base * const base = FACTORY->find( URL ); if( base ) return base; }
    IF_FIND_RETURN( nodeFactory_, refinedURL );
    IF_FIND_RETURN( geometryFactory_, refinedURL );
#undef IF_FIND_RETURN

    return NULL;
}



}
