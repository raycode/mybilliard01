#pragma once

namespace core_billiard {


template< typename TypeTo, typename TypeFrom >
TypeTo convertString( typename TypeFrom input ) {
    return TypeTo( input.begin(), input.end() );
}


}