#pragma once
#include "stdafx.h"

namespace my_render {
    using namespace std;
    using namespace std::tr1;

    class ApplicationWindow;
    class MouseEventListener;
    class KeyboardEventListener;

    class Render;
    class RenderEventListener;

    class RenderTarget;
    class RenderTargetCallBack;

    class RenderState;
    class RenderState_Wireframe;
    class RenderState_Cull;

    class Shader;
    class Texture;
    class EffectShader;
    class EffectShaderCallBack;
    class ShaderVariable;
    class EffectShaderAnnotation;
    class EffectShaderVariable;
    class EffectShaderVariableBlock;
    class EffectShaderVariableBlockCallBack;

    class VertexBuffer;
    class RenderBufferFactory;

    class Scene;

    class Base;
    class Node;
    class Camera;

    class ColladaFactory;
    class NodeFactory;
    class GeometryFactory;
    class Instance;
    class InstanceResolver;

    class Geometry;
    class GeometryMesh;
    class GeometryMeshPrimitive;

    class CameraFactory;
    class CameraPerspective;
    class CameraOrthographic;

    MY_SMART_PTR( ApplicationWindow );
    MY_SMART_PTR( MouseEventListener );
    MY_SMART_PTR( KeyboardEventListener );
    MY_SMART_PTR( Render );
    MY_SMART_PTR( RenderState );
    MY_SMART_PTR( RenderTarget );
    MY_SMART_PTR( RenderTargetCallBack );
    MY_SMART_PTR( RenderEventListener );
    MY_SMART_PTR( VertexBuffer );
    MY_SMART_PTR( Texture );
    MY_SMART_PTR( Shader );
    MY_SMART_PTR( ShaderVariable );
    MY_SMART_PTR( EffectShaderAnnotation );
    MY_SMART_PTR( EffectShaderVariable );
    MY_SMART_PTR( EffectShaderVariableBlock );
    MY_SMART_PTR( EffectShaderVariableBlockCallBack );
    MY_SMART_PTR( EffectShaderCallBack );
    MY_SMART_PTR( EffectShader );
    MY_SMART_PTR( RenderBufferFactory );
    MY_SMART_PTR( Scene );
    MY_SMART_PTR( Base );
    MY_SMART_PTR( Node );
    MY_SMART_PTR( Camera );
    MY_SMART_PTR( ColladaFactory );
    MY_SMART_PTR( NodeFactory );
    MY_SMART_PTR( GeometryFactory );
    MY_SMART_PTR( Instance );
    MY_SMART_PTR( InstanceResolver );
    MY_SMART_PTR( Geometry );
    MY_SMART_PTR( GeometryMesh );
    MY_SMART_PTR( GeometryMeshPrimitive );
    MY_SMART_PTR( CameraFactory );
    MY_SMART_PTR( CameraPerspective );
    MY_SMART_PTR( CameraOrthographic );
}

#include "RenderTargetCallBack.h"
#include "RenderTarget.h"

#include "ApplicationWindow.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"
#include "MouseEventListenerNull.hpp"
#include "KeyboardEventListenerNull.hpp"

#include "VertexBuffer.h"
#include "RenderBufferFactory.h"
#include "RenderBufferFactoryNull.hpp"

#include "Texture.h"
#include "Shader.h"
#include "ShaderVariable.h"
#include "ShaderVariableNull.hpp"
#include "EffectShaderCallBack.h"
#include "EffectShaderAnnotation.h"
#include "EffectShaderVariable.h"
#include "EffectShaderVariableBlock.h"
#include "EffectShaderVariableBlockCallBack.h"
#include "EffectShader.h"

#include "RenderState_Wireframe.h"
#include "RenderState_WireframeNull.hpp"
#include "RenderState_Cull.h"
#include "RenderState_CullNull.hpp"
#include "RenderState.h"
#include "RenderStateNull.hpp"

#include "RenderEventListener.h"
#include "RenderEventListenerNull.hpp"
#include "Render.h"
#include "RenderNull.hpp"
#include "Scene.h"

#include "Base.h"
#include "BaseNull.hpp"
#include "Node.h"
#include "NodeNull.hpp"
#include "Camera.h"

#include "ColladaFactory.h"
#include "NodeFactory.h"
#include "GeometryFactory.h"
#include "Instance.h"
#include "InstanceResolver.h"

#include "Geometry.h"
#include "GeometryMesh.h"
#include "GeometryMeshPrimitive.h"

#include "CameraCommon.h"
#include "CameraFactory.h"
#include "CameraPerspective.h"
#include "CameraOrthographic.h"
