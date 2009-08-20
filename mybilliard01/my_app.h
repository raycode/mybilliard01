#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "resource.h"

#include "../core_billiard/my_phys.h"
#include "../render_win32/my_render_win32_dx9_imp.h"

#pragma warning( disable: 4201 )
#include "tinyxml.h"

#include "targetver.h"


using namespace std;
using namespace my_render;
using namespace my_render_win32;
using namespace my_render_win32_dx9;

using namespace my_render_imp;
using namespace my_render_win32_imp;
using namespace my_render_win32_dx9_imp;

using namespace my_phys;

class RenderEventListenerImp;
class InputListenerImp;
class MyCamera;

MY_SMART_PTR( RenderEventListenerImp );
MY_SMART_PTR( InputListenerImp );
MY_SMART_PTR( MyCamera );

#include "MyCamera.h"
#include "RenderEventListenerImp.h"
#include "InputListenerImp.h"
#include "ConstString.h"
