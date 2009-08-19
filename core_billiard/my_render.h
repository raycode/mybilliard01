#pragma once
#include "stdafx.h"

namespace my_render {
    using namespace std;

    class ApplicationWindow;
    class MouseEventListener;
    class KeyboardEventListener;

    class SurfaceLockedRect;
    class Surface;
    class Render;
    class RenderEventListener;

    class RenderState;
    class RenderState_Wireframe;
    class RenderState_Cull;

    class Shader;
    class Texture;
    class VertexShader;
    class PixelShader;
    class EffectShader;
    class ShaderVariableWriter;
    class RenderEffectShader;
    class ShaderVariable;

    class VertexBuffer;
    class IndexBuffer;
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
    MY_SMART_PTR( SurfaceLockedRect );
    MY_SMART_PTR( Surface );
    MY_SMART_PTR( Render );
    MY_SMART_PTR( RenderState );
    MY_SMART_PTR( RenderEventListener );
    MY_SMART_PTR( VertexBuffer );
    MY_SMART_PTR( IndexBuffer );
    MY_SMART_PTR( Texture );
    MY_SMART_PTR( Shader );
    MY_SMART_PTR( ShaderVariable );
    MY_SMART_PTR( ShaderVariableWriter );
    MY_SMART_PTR( VertexShader );
    MY_SMART_PTR( PixelShader );
    MY_SMART_PTR( RenderEffectShader );
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

#include "ApplicationWindow.h"
#include "MouseEventListener.h"
#include "KeyboardEventListener.h"
#include "MouseEventListenerNull.hpp"
#include "KeyboardEventListenerNull.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderBufferFactory.h"
#include "RenderBufferFactoryNull.hpp"

#include "ShaderVariableWriter.h"
#include "Texture.h"
#include "Shader.h"
#include "ShaderVariable.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RenderEffectShader.h"
#include "EffectShader.h"

#include "RenderState_Wireframe.h"
#include "RenderState_WireframeNull.hpp"
#include "RenderState_Cull.h"
#include "RenderState_CullNull.h"
#include "RenderState.h"
#include "RenderStateNull.hpp"

#include "RenderEventListener.h"
#include "RenderEventListenerNull.hpp"
#include "SurfaceLockedRect.h"
#include "Surface.h"
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
