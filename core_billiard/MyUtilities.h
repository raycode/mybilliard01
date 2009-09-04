#pragma once

#include "static_check.h"



#define MY_FOR_EACH( CONTAINER_TYPE, ITERATOR, CONTAINER ) \
    for( CONTAINER_TYPE::const_iterator ITERATOR = (CONTAINER).begin(); ITERATOR != (CONTAINER).end(); ++ITERATOR )

#define MY_FOR_EACH_MODIFY( CONTAINER_TYPE, ITERATOR, CONTAINER ) \
    for( CONTAINER_TYPE::iterator ITERATOR = (CONTAINER).begin(); ITERATOR != (CONTAINER).end(); ++ITERATOR )

#define MY_FOR_EACH_COLLADA( VALUE_TYPE, ITERATOR, CONTAINER ) \
    VALUE_TYPE##_Array colladaContainer_##ITERATOR = (CONTAINER); \
    vector< VALUE_TYPE##Ref > STL_##ITERATOR; \
    if( colladaContainer_##ITERATOR.getCount() > 0 ) STL_##ITERATOR = vector< VALUE_TYPE##Ref >( &(colladaContainer_##ITERATOR[ 0 ]), &(colladaContainer_##ITERATOR[ 0 ]) + colladaContainer_##ITERATOR.getCount() ); \
    for( vector< VALUE_TYPE##Ref >::iterator ITERATOR = STL_##ITERATOR.begin(); ITERATOR != STL_##ITERATOR.end() && NULL != *ITERATOR; ++ITERATOR )

#define MY_FAST_FOR_EACH_VECTOR( CONTAINER_TYPE, ITER, CONTAINER ) \
    CONTAINER_TYPE::value_type * ITER = ( CONTAINER.size() != 0u ) ? ITER = &(CONTAINER.at( 0u )) : NULL; \
    for( size_t i_##ITER = 0u, CONTAINER_SIZE = CONTAINER.size(); i_##ITER < CONTAINER_SIZE; actor =  ++(i_##ITER), ++(##ITER) )


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

inline std::wstring convertString( char * input ) {
    if( NULL == input ) return L"";
    return convertString< std::wstring, std::string >( input );
}

inline std::string convertString( wchar_t * input ) {
    if( NULL == input ) return "";
    return convertString< std::string, std::wstring >( input );
}

inline std::wstring convertString( const char * input ) {
    if( NULL == input ) return L"";
    return convertString< std::wstring, std::string >( input );
}

inline std::string convertString( const wchar_t * input ) {
    if( NULL == input ) return "";
    return convertString< std::string, std::wstring >( input );
}


template<typename T, std::size_t N>
static std::size_t size_of(T(&)[N])
{
    return N;
}


template < typename T1 >
static T1 * daeDowncast( daeElement * elem ) {
    if( NULL == elem ) return NULL;
    if( T1::ID() != elem->typeID() ) return NULL;
    return (T1*) elem;
}


}


#include <memory>

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef std::tr1::shared_ptr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef std::tr1::shared_ptr< const CLASS_NAME > CLASS_NAME##ConstPtr 

template< typename T >
struct ComReleaser
{
    void operator()( T * comObject) const {
        if( NULL == comObject ) return;
        comObject->Release();
    }
};

template< typename T1, typename T2 >
static bool remove_only_one_pointer( T1 & aList, T2 val ) {
    for( T1::const_iterator iter = aList.begin(); iter != aList.end(); ++iter ) {
        if( val != iter->get() ) continue;
        aList.erase( iter );
        return true;
    }
    return false;
}



#pragma warning ( disable : 4250 )

#define NULL_OBJECT( INTERFACE_NAME ) struct INTERFACE_NAME##Null : public virtual INTERFACE_NAME 
#define MY_INTERFACE struct
#define IMPLEMENTS_INTERFACE( INTERFACE_NAME ) public virtual INTERFACE_NAME
#define EXTENDS_INTERFACE( INTERFACE_NAME ) public virtual INTERFACE_NAME

// sometimes we need to use static_cast rather than dynamic_cast for performance reason.
#define STATIC_EXTENDS_INTERFACE( INTERFACE_NAME ) public INTERFACE_NAME
// but there shouldn't be any case to down cast to implementation level.
//#define IMPLEMENTS_STATIC_( INTERFACE_NAME ) public INTERFACE_NAME


#define MY_UNIT_TEST_BACKDOOR public: struct TestingBackdoor; private: struct __Semicolon_Is_Missing__



#pragma warning ( disable : 4481 )

#if defined(_MSC_VER)
#define OVERRIDE override
#else
#define OVERRIDE  
#endif



//#ifdef DEBUG

#define CONTINUE_UNLESS( CONDITION ) if(!(CONDITION)) { assert( L#CONDITION && false ); continue; }
#define RETURN_VOID_UNLESS( CONDITION ) if(!(CONDITION)) { assert( L#CONDITION && false ); return; }
#define RETURN_VALUE_UNLESS( CONDITION, VALUE ) if(!(CONDITION)) { assert(L#CONDITION && false);return VALUE;}
#define THROW_UNLESS( CONDITION, EXCEPTION ) if(!(CONDITION)) { assert(L#CONDITION && false);throw EXCEPTION;}

//#endif


