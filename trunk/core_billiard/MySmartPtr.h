#pragma once

#define MY_SMART_PTR_USE_TR1



#ifdef MY_SMART_PTR_USE_TR1

#include <memory>

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef std::tr1::shared_ptr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef std::tr1::shared_ptr< const CLASS_NAME > CLASS_NAME##ConstPtr 


#else

#pragma warning ( disable : 4819 )

#include "loki/SmartPtr.h"

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef Loki::SmartPtr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef Loki::SmartPtr< const CLASS_NAME > CLASS_NAME##ConstPtr 

#endif


namespace Loki {}