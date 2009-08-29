#pragma once
#include "Stdafx.h"

namespace my_open_al
{
    using namespace std;
    using namespace std::tr1;

    class MyOpenAL;
    class SoundHandle;

    MY_SMART_PTR( MyOpenAL );
    MY_SMART_PTR( SoundHandle );
}

#include "Utilities.h"

#include "MyOpenAL.h"
#include "SoundHandle.h"
