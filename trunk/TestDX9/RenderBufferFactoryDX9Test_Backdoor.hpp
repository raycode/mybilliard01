#pragma once

#define PRIVATE_METHOD( CLASS_NAME, methodName ) CLASS_NAME::TestingBackdoor::methodName
#define PRIVATE_METHOD_0( returnType, CLASS_NAME, methodName ) static returnType methodName( CLASS_NAME * obj ) { return obj->methodName(); }
#define PRIVATE_METHOD_4( returnType, CLASS_NAME, methodName, arg0, arg1, arg2, arg3 ) static returnType methodName( CLASS_NAME,  * obj, arg0 a0, arg1 a1, arg2 a2, arg3 a3 ) { return obj->methodName( a0, a1, a2, a3 ); }
#define PRIVATE_METHOD_0_VOID( CLASS_NAME, methodName ) static void methodName( CLASS_NAME,  * obj ) { obj->methodName(); }
#define PRIVATE_MEMBER( memberType, CLASS_NAME, memberName ) static memberType & memberName( CLASS_NAME * obj ) { return obj->memberName; }

struct RenderBufferFactoryDX9Imp::TestingBackdoor {
};

struct VertexBufferDX9Imp::TestingBackdoor {
    PRIVATE_METHOD_0( size_t, VertexBufferDX9Imp, updateOffset );
    PRIVATE_MEMBER( vector< D3DVERTEXELEMENT9 >, VertexBufferDX9Imp, vertexElementDX9_ );
};


struct RenderWin32DX9Imp::TestingBackdoor {
    PRIVATE_METHOD_0( RenderBufferFactoryDX9 *, RenderWin32DX9Imp, getBufferFactory );
};

