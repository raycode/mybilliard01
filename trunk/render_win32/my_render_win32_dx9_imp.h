#pragma once
#include "DXUT.h"
//#include "SDKmisc.h"
#include "my_render_win32_dx9.h"
#include "my_render_win32_imp.h"


namespace my_render_win32_dx9_imp {
    using namespace std;
    using namespace std::tr1;
    using namespace my_utility;

    using namespace my_render;
    using namespace my_render_win32;
    using namespace my_render_win32_dx9;

    using namespace my_render_imp;
    using namespace my_render_win32_imp;

    class SurfaceLockedRectDX9Imp;
    class SurfaceDX9Imp;
    class RenderTargetDX9Imp;
    class DepthStensilDX9Imp;

    class VertexBufferDX9Imp;
    class TextureDX9Imp;
    class EffectShaderDX9Imp;
    class EffectShaderVariableDX9Imp;
    class EffectShaderVariableBlockDX9Imp;
    class EffectShaderAnnotationDX9Imp;

    class RenderBufferFactoryDX9Imp;
    class RenderWin32DX9Imp;

    class RenderStateDX9Imp;
    class RenderState_WireframeDX9Imp;
    class RenderState_CullDX9Imp;

    MY_SMART_PTR( SurfaceDX9Imp );
    MY_SMART_PTR( SurfaceLockedRectDX9Imp );
    MY_SMART_PTR( RenderTargetDX9Imp );
    MY_SMART_PTR( DepthStensilDX9Imp );

    MY_SMART_PTR( VertexBufferDX9Imp );
    MY_SMART_PTR( TextureDX9Imp );
    MY_SMART_PTR( EffectShaderDX9Imp );
    MY_SMART_PTR( EffectShaderVariableDX9Imp );
    MY_SMART_PTR( EffectShaderVariableBlockDX9Imp );
    MY_SMART_PTR( EffectShaderAnnotationDX9Imp );

    MY_SMART_PTR( RenderBufferFactoryDX9Imp );
    MY_SMART_PTR( RenderWin32DX9Imp );

    MY_SMART_PTR( RenderStateDX9Imp );
    MY_SMART_PTR( RenderState_WireframeDX9Imp );
    MY_SMART_PTR( RenderState_CullDX9Imp );
}

#include "SurfaceLockedRectDX9Imp.h"
#include "SurfaceDX9Imp.h"
#include "RenderTargetDX9Imp.h"
#include "DepthStensilDX9Imp.h"

#include "VertexBufferDX9Imp.h"
#include "TextureDX9Imp.h"
#include "EffectShaderDX9Imp.h"
#include "EffectShaderVariableDX9Imp.h"
#include "EffectShaderVariableBlockDX9Imp.h"
#include "EffectShaderAnnotationDX9Imp.h"

#include "RenderBufferFactoryDX9Imp.h"
#include "RenderWin32DX9Imp.h"

#include "RenderStateDX9Imp.h"
#include "RenderState_WireframeDX9Imp.h"
#include "RenderState_CullDX9Imp.h"


#define RETURN_FALSE_IF_FAILED( HR, MSG )   if( FAILED( HR ) ) { DXUT_ERR( MSG, HR ); return false; }
#define RETURN_NULL_IF_FAILED( HR, MSG )   if( FAILED( HR ) ) { DXUT_ERR( MSG, HR ); return NULL; }

