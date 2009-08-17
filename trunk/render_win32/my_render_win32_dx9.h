#pragma once
#include "my_render_win32.h"

namespace my_render_win32_dx9 {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;
    using namespace my_render_win32;

    class ReleasableResourceDX9;
    class VertexBufferDX9;
    class IndexBufferDX9;
    class EffectShaderDX9;
    class RenderBufferFactoryDX9;
    class RednerWin32DX9;
    class ShaderVariableDX9;
    class ShaderVariableEffectDX9;
    class SurfaceDX9;

    class RenderStateDX9;
    class RenderState_WireframeDX9;
    class RenderState_CullDX9;

    MY_SMART_PTR( ReleasableResourceDX9 );
    MY_SMART_PTR( VertexBufferDX9 );
    MY_SMART_PTR( IndexBufferDX9 );
    MY_SMART_PTR( EffectShaderDX9 );
    MY_SMART_PTR( RenderBufferFactoryDX9 );
    MY_SMART_PTR( ShaderVariableDX9 );
    MY_SMART_PTR( ShaderVariableEffectDX9 );
    MY_SMART_PTR( SurfaceDX9 );

    MY_SMART_PTR( RenderStateDX9 );
    MY_SMART_PTR( RenderState_WireframeDX9 );
    MY_SMART_PTR( RenderState_CullDX9 );
}

#include "ReleasableResourceDX9.h"
#include "EffectShaderDX9.h"
#include "RenderBufferFactoryDX9.h"
#include "RenderBufferFactoryDX9Null.hpp"
#include "VertexBufferDX9.h"
#include "IndexBufferDX9.h"
#include "RenderWin32DX9.h"
#include "ShaderVariableDX9.h"
#include "ShaderVariableEffectDX9.h"
#include "SurfaceDX9.h"

#include "RenderStateDX9.h"
#include "RenderState_WireframeDX9.h"
#include "RenderState_CullDX9.h"
