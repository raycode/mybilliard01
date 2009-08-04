#pragma once

#pragma warning ( disable : 4819 )
#include "loki/SmartPtr.h"

#define MY_SMART_PTR( CLASS_NAME ) \
    typedef Loki::SmartPtr< CLASS_NAME > CLASS_NAME##Ptr; \
    typedef Loki::SmartPtr< const CLASS_NAME > CLASS_NAME##ConstPtr 