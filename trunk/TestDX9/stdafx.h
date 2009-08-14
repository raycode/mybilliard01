// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once
#include <deque>

#include "../dxut/Core/DXUT.h"
#include "../render_win32/my_render_win32_dx9_imp.h"
#include "../TestProject1/MyTestingUtility.hpp"

using namespace std;
using namespace my_render;
using namespace my_render_win32;
using namespace my_render_win32_dx9;

using namespace my_render_imp;
using namespace my_render_win32_imp;
using namespace my_render_win32_dx9_imp;

using namespace MyTestingUtility;

#include "BackbufferHelper.hpp"


#define assertTrue( obj ) { Assert::IsTrue( obj ); }
#define assertFalse( obj ) { Assert::IsFalse( obj ); }
#define assertEquals( expect, actual ) { Assert::AreEqual( expect, actual ); }
#define assertStrEquals( expect, actual ) { Assert::AreEqual( getString( expect ), getString( actual ) ); }
#define assertNull( obj ) { Assert::IsTrue( NULL == obj ); }
#define assertNotNull( obj ) { Assert::IsTrue( NULL != obj ); }
#define fail { Assert::Fail(); }

