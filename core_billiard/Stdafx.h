#pragma once

#ifdef WIN32 
#	define NOMINMAX
#	include <windows.h>
#endif

#if defined(_XBOX)
#	include <xtl.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <cassert>
#include <memory>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#include "NxPhysics.h"
#include "NxSimpleTypes.h"
#include "NxMat34.h"

#include "al/al.h"
#include "al/alc.h"
#include "al/alu.h"
#include "al/alut.h"

#pragma warning ( disable : 4819 )

#include "dae.h"
#include "dom/domTypes.h"
#include "dom/domCOLLADA.h"

#include "MyUtilities.h"

MY_SMART_PTR( DAE );
