#pragma once

#define MY_ITERATOR_DECL( CLASS_NAME ) \
    typedef CLASS_NAME::const_iterator CLASS_NAME##Iterator;\
    typedef CLASS_NAME::iterator CLASS_NAME##ModifiableIterator;


namespace my_utility {


template< typename TypeTo, typename TypeFrom >
TypeTo convertString( typename TypeFrom input ) {
    return TypeTo( input.begin(), input.end() );
}


}