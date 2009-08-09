#pragma once

#include <cassert>


#define MY_FOR_EACH( STL_TYPE, VAR_ITER, STL_CONTAINNER ) \
    STL_TYPE::const_iterator VAR_ITER = STL_CONTAINNER.begin();\
    for( ; VAR_ITER != STL_CONTAINNER.end(); ++VAR_ITER )

#define MY_FOR_EACH_MOD( STL_TYPE, VAR_ITER, STL_CONTAINNER ) \
    STL_TYPE::iterator VAR_ITER = STL_CONTAINNER.begin();\
    for( ; VAR_ITER != STL_CONTAINNER.end(); ++VAR_ITER )


namespace my_utility {


template< typename TypeTo, typename TypeFrom >
TypeTo convertString( typename TypeFrom input ) {
    return TypeTo( input.begin(), input.end() );
}

inline std::wstring convertString( std::string input ) {
    return convertString< std::wstring, std::string >( input );
}

inline std::string convertString( std::wstring input ) {
    return convertString< std::string, std::wstring >( input );
}


}


#define MY_SMART_PTR_USE_TR1

#ifdef MY_SMART_PTR_USE_TR1

#include <memory>

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef std::tr1::shared_ptr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef std::tr1::shared_ptr< const CLASS_NAME > CLASS_NAME##ConstPtr 

namespace Loki {}

#else

#pragma warning ( disable : 4819 )

#include "loki/SmartPtr.h"

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef Loki::SmartPtr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef Loki::SmartPtr< const CLASS_NAME > CLASS_NAME##ConstPtr 

#endif


#pragma warning ( disable : 4250 )

#define INTERFACE_ class
#define IMPLEMENTS_( INTERFACE_NAME ) public virtual INTERFACE_NAME
#define EXTENDS_INTERFACE_( INTERFACE_NAME ) public virtual INTERFACE_NAME


template < typename T1 >
static T1 * daeDowncast( daeElement * elem ) {
    if( NULL == elem ) return NULL;
    if( T1::ID() != elem->typeID() ) return NULL;
    return (T1*) elem;
}
