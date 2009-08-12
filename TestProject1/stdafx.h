// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define NOMINMAX
#include <windows.h>
#include <vcclr.h>

#include <iostream>
#include <fstream>

#include "../core_billiard/stdafx.h"
#include "../core_billiard/my_render_imp.h"
#include "../render_win32/my_render_win32_dx9_imp.h"

using namespace std;
using namespace my_render;
using namespace my_render_imp;
using namespace my_render_win32_dx9_imp;
//using namespace billiard;

#include "MyTestingUtility.hpp"
#include "DummyBaseFactory.hpp"

using namespace MyTestingUtility;
