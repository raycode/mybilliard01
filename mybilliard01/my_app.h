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

class MyRenderEventListenerImp;
class MyInputListenerImp;
class MyCamera;
class EffectShaderFeeder;

MY_SMART_PTR( MyRenderEventListenerImp );
MY_SMART_PTR( MyInputListenerImp );
MY_SMART_PTR( MyCamera );
MY_SMART_PTR( EffectShaderFeeder );

#include "MyCamera.h"
#include "MyInputListenerImp.h"
#include "EffectShaderFeeder.h"
#include "EffectShaderFeederNull.hpp"
#include "RenderMonkeySemantics.hpp"
#include "RenderMonkeySemanticFeeder.h"
#include "RenderMonkeySharedSemanticsFeeder.h"
#include "MyRenderEventListenerImp.h"
#include "ConstString.h"

