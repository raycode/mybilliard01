#include "my_render_imp.h"
namespace my_render_imp {

Base * FactoryImp::resolveInstanceUrl( wstring url ) {

#define IF_FIND_RETURN( FACTORY, URL ) { Base * base = FACTORY->find( URL ); if( base ) return base; }
    IF_FIND_RETURN( nodeFactory_, url );
    IF_FIND_RETURN( geometryFactory_, url );

    return NULL;
}

FactoryImp::FactoryImp()
: nodeFactory_( new NodeFactoryImp( this ) )
, geometryFactory_( new GeometryFactoryImp( this ) )
{
}




}
