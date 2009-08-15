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

        bool isVertexUploaded( VertexBuffer * vb ) {
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
            assertNotNull( vb );
            assertEquals( 3u, vb->getNumberOfVertex() );

            VertexBufferDX9Imp * const vbImp = dynamic_cast< VertexBufferDX9Imp* >( vb );
            assertNotNull( vbImp );
            assertEquals( sizeof(float) * 9 , vbImp->getSizeInByteForTotal() );
            assertEquals( sizeof(float) * 3, vbImp->getSizeInByteForEachVertex() );

            assertTrue( factory->releaseVertexBuffer( vb ) );
        };

        [TestMethod]
        void UploadVertexBufferOntoMemory()
        {
            VertexBuffer * const vb = factory->createVertexBuffer_static( 3, positions );
            assertNotNull( vb );
            
            factory->update( NULL, 0.f );
            assertTrue( isVertexUploaded( vb ) );

            assertTrue( factory->releaseVertexBuffer( vb ) );
        }

        [TestMethod]
        void RenderVertexBuffer()
        {
            //VertexBufferDX9Imp * const vbImp
            //    = dynamic_cast< VertexBufferDX9Imp* >( factory->createVertexBuffer_static( 1, positions ) );
            //assertNotNull( vbImp );
        }

    };
}
