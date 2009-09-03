#include "Stdafx.h"
#include "my_render.h"
namespace my_render {

#ifdef DEBUG
    RenderNull nullRender__;
    KeyboardEventListenerNull nullKeyboardEventListener__;
    MouseEventListenerNull nullMouseEventListener__;
    RenderEventListenerNull nullRenderEventListener__;
    RenderBufferFactoryNull nullRenderBufferFactory__; 
    RenderStateNull nullRenderState__; 
    RenderState_WireframeNull nullRenderState_Wireframe__; 
    RenderState_CullNull nullRenderState_Cull__; 
    ShaderVariableNull nullShaderVariable__;
    EffectShaderFeederNull nullEffectShaderFeeder__;
#endif

}

