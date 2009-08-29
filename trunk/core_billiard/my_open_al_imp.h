#pragma once
#include "my_open_al.h"

namespace my_open_al_imp
{
    using namespace std;
    using namespace std::tr1;
    using namespace my_utility;
    using namespace my_open_al;

    class MyOpenALImp;
    class SoundHandleImp;

    MY_SMART_PTR( MyOpenALImp );
    MY_SMART_PTR( SoundHandleImp );
}

#include "MyOpenALImp.h"
#include "SoundHandleImp.h"

