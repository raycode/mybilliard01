#pragma once
#include "my_render_win32.h"

namespace my_render_win32_dx9 {
    using namespace std;
    using namespace my_utility;
    using namespace my_render;
    using namespace my_render_win32;

    class VertexBufferDX9;
    class IndexBufferDX9;
    class EffectShaderDX9;
    class RenderBufferFactoryDX9;
    class NullRenderBufferFactoryDX9;
    class RednerWin32DX9;
    class ShaderVariableDX9;

    MY_SMART_PTR( VertexBufferDX9 );
    MY_SMART_PTR( IndexBufferDX9 );
    MY_SMART_PTR( EffectShaderDX9 );
    MY_SMART_PTR( RenderBufferFactoryDX9 );
    MY_SMART_PTR( NullRenderBufferFactoryDX9 );
    MY_SMART_PTR( ShaderVariableDX9 );
}

#include "EffectShaderDX9.h"
#include "RenderBufferFactoryDX9.h"
#include "NullRenderBufferFactoryDX9.hpp"
#include "VertexBufferDX9.h"
#include "IndexBufferDX9.h"
#include "RenderWin32DX9.h"
#include "ShaderVariableDX9.h"
