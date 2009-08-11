#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "resource.h"

#include "my_render_win32_d3d9_imp.h"


using namespace std;
using namespace my_render;
using namespace my_render_win32;
using namespace my_render_win32_d3d9;

using namespace my_render_imp;
using namespace my_render_win32_imp;
using namespace my_render_win32_d3d9_imp;


class RenderErrorListenerImp;
class RenderEventListenerImp;
class InputListenerImp;

MY_SMART_PTR( RenderErrorListenerImp );
MY_SMART_PTR( RenderEventListenerImp );
MY_SMART_PTR( InputListenerImp );

#include "RenderErrorListenerImp.h"
#include "RenderEventListenerImp.h"
#include "InputListenerImp.h"
#include "ConstString.h"
