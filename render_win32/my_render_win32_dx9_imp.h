#pragma once
#include "DXUT.h"
//#include "SDKmisc.h"
#include "my_render_win32_dx9.h"
#include "my_render_win32_imp.h"


namespace my_render_win32_dx9_imp {
    using namespace std;
    using namespace my_utility;

    using namespace my_render;
    using namespace my_render_win32;
    using namespace my_render_win32_dx9;

    using namespace my_render_imp;
    using namespace my_render_win32_imp;

    class SurfaceLockedRectDX9Imp;
    class SurfaceDX9Imp;

    class VertexBufferDX9Imp;
    class IndexBufferDX9Imp;
    class EffectShaderDX9Imp;
    class ShaderVariableEffectDX9Imp;

    class RenderBufferFactoryDX9Imp;
    class RenderWin32DX9Imp;

    class RenderStateDX9Imp;
    class RenderState_WireframeDX9Imp;

    MY_SMART_PTR( SurfaceDX9Imp );
    MY_SMART_PTR( SurfaceLockedRectDX9Imp );

    MY_SMART_PTR( VertexBufferDX9Imp );
    MY_SMART_PTR( IndexBufferDX9Imp );
    MY_SMART_PTR( EffectShaderDX9Imp );
    MY_SMART_PTR( ShaderVariableEffectDX9Imp );

    MY_SMART_PTR( RenderBufferFactoryDX9Imp );
    MY_SMART_PTR( RenderWin32DX9Imp );

    MY_SMART_PTR( RenderStateDX9Imp );
    MY_SMART_PTR( RenderState_WireframeDX9Imp );
}

#include "SurfaceLockedRectDX9Imp.h"
#include "SurfaceDX9Imp.h"

#include "VertexBufferDX9Imp.h"
#include "IndexBufferDX9Imp.h"
#include "EffectShaderDX9Imp.h"
#include "ShaderVariableEffectDX9Imp.h"

#include "RenderBufferFactoryDX9Imp.h"
#include "RenderWin32DX9Imp.h"

#include "RenderStateDX9Imp.h"
#include "RenderState_WireframeDX9Imp.h"
