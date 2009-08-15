#include "stdafx.h"
#include "RenderBufferFactoryDX9Test_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestDX9
{
    const static float positions[] = {
        150.0f,  50.0f, 0.5f,
        250.0f, 250.0f, 0.5f,
        50.0f, 250.0f, 0.5f
    };

    const static NxU32 diffuses[] = {
        0xffff0000, 0xff00ff00, 0xff00ffff
    };

	[TestClass]
	public ref class RenderBufferFactoryDX9Test
	{
    private:
        RenderWin32DX9Imp * dx9Imp;
        RenderBufferFactoryDX9 * factory;

    public: 
        [TestInitialize()]
        void MyTestInitialize() {
            dx9Imp = new RenderWin32DX9Imp();
            dx9Imp->setBackbufferLockable( true );
            Assert::IsTrue( dx9Imp->createDevice( true, 30, 30 ) );
            factory = PRIVATE_METHOD( RenderWin32DX9Imp, getBufferFactory )( dx9Imp );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            dx9Imp->destroyDevice();
            delete dx9Imp;
        };

        static bool isSizeCorrect( VertexBuffer * vb, size_t nVertex, size_t sizeEachVertex, size_t nElements ) {
            VertexBufferDX9Imp * const vbImp = dynamic_cast< VertexBufferDX9Imp* >( vb );
            if( NULL == vbImp ) return false;
            if( nVertex != vbImp->getNumberOfVertex() ) return false;
            if( sizeEachVertex != vbImp->getSizeInByteForEachVertex() ) return false;
            if( nVertex * sizeEachVertex != vbImp->getSizeInByteForTotal() ) return false;
            if( D3DDECLTYPE_UNUSED != vbImp->getVertexElement()[ nElements ].Type ) return false;
            return true;
        }

        static bool isVertexUploaded( VertexBuffer * vb ) {
            VertexBufferDX9Imp * const vbImp = dynamic_cast< VertexBufferDX9Imp* >( vb );
            if( NULL == vbImp ) return false;

            LPDIRECT3DVERTEXBUFFER9 vbDX9 = vbImp->getVertexBufferDX9();
            if( NULL == vbDX9 ) return false;

            D3DVERTEXBUFFER_DESC desc;
            vbDX9->GetDesc( &desc );
            if( 0 != desc.FVF ) return false;
            if( (int) D3DPOOL_DEFAULT != (int) desc.Pool ) return false;
            if( vbImp->getSizeInByteForTotal() != desc.Size ) return false;

            return true;
        }

    public:
		[TestMethod]
		void FixtureTesting()
		{
		};

        [TestMethod]
        void CreateVertexBuffer_static()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3, 1 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void UploadVertexBufferOntoMemory()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            factory->update( NULL, 0.f );
            assertTrue( isVertexUploaded( vb ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        }

        [TestMethod]
        void CreateVertexBuffer_static_Normal0()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendNormal_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 * 2, 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_Normal1()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendNormal_Array( positions, 1 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 * 2, 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_TwoNormals()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendNormal_Array( positions, 0 ) );
            assertTrue( vb->appendNormal_Array( positions, 1 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 * 3, 3 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_TexCoord1D()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendTexCoord1D_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 + sizeof( float ), 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_TexCoord2D()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendTexCoord2D_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 + sizeof( float ) * 2, 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_TexCoord3D()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendTexCoord3D_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 + sizeof( float ) * 3, 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void CreateVertexBuffer_static_Color()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendColor_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 + sizeof( DWORD ), 2 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        }

        [TestMethod]
        void CreateVertexBuffer_static_Normal_TexCoord2_Color()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendNormal_Array( positions, 0 ) );
            assertTrue( vb->appendTexCoord2D_Array( positions, 0 ) );
            assertTrue( vb->appendColor_Array( positions, 0 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 *2 + sizeof(float)*2 + sizeof( DWORD ), 4 ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        }

        [TestMethod]
        void CreateVertexBuffer_static_TexCoord2D_DuplicatedUsageOffset()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertTrue( vb->appendTexCoord2D_Array( positions, 1 ) );
            assertFalse( vb->appendTexCoord2D_Array( positions, 1 ) );
            assertTrue( isSizeCorrect( vb, 3, sizeof(float) * 3 + sizeof( float ) * 2, 2 /*not 3*/ ) );
            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void RenderVertexBuffer()
        {
        }

    };
}
