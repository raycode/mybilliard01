#pragma once
#include "DXUT.h"
#include "SDKmisc.h"
#include "SDKmesh.h"
#include "resource.h"

#include "../../core_billiard/my_render_imp.h"
#include "my_render_d3d9_imp.h"

#include "ConstString.h"

using namespace std;
using namespace my_render;
using namespace my_render_imp;
using namespace my_render_d3d9_imp;

#include "RenderErrorListenerImp.h"
#include "RenderEventListenerImp.h"

MY_SMART_PTR( RenderErrorListenerImp );
MY_SMART_PTR( RenderEventListenerImp );
