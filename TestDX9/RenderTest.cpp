#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


class RenderListener_clear : public NullRenderEventListener {
public:
    void setClearColor( NxU32 clearColor ) { clearColor_ = clearColor; }
    NxU32 getClearColor() const { return clearColor_; }

public:
    virtual void display( Render * render ) OVERRIDE {
        render->clear( ERenderClear_TARGET, clearColor_, 1.f, 0 );
    }

private:
    NxU32 clearColor_;
};


namespace TestDX9
{
	[TestClass]
	public ref class RenderTest
	{
    private:
        static TestContext^ testContextInstance;

    private:
        RenderWin32DX9 * dx9;
        RenderBufferFactory * factory;

    public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize() {
            dx9 = new RenderWin32DX9Imp();
            dx9->setBackbufferLockable( true );
            Assert::IsTrue( dx9->createDevice( true, 30, 30 ) );
            //factory = new RenderBufferFactoryDX9Imp( dx9->getD3D9() );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            //delete factory;
            dx9->destroyDevice();
            delete dx9;
        };

    public:
        [TestMethod]
        void FixtureOnly() {
        }

		[TestMethod]
		void Render_Clear()
		{
            RenderListener_clear * const evt = new RenderListener_clear();
            dx9->addRenderEventListener( evt );

            evt->setClearColor( PixelColor( 255, 0, 0, 0 ) );
            dx9->render();
            //{
            //    BackbufferHelper backbuffer( factory );
            //    NxU32 * const ptr = backbuffer.getBitPointer();
            //    Assert::IsTrue( NULL != ptr );
            //    Assert::AreEqual( evt->getClearColor() & 0xffffff, ptr[10] & 0xffffff );
            //}

            //evt->setClearColor( PixelColor( 255, 256, 0, 0 ) );
            //dx9->render();
            //{
            //    BackbufferHelper backbuffer( factory );
            //    NxU32 * const ptr = backbuffer.getBitPointer();
            //    Assert::IsTrue( NULL != ptr );
            //    Assert::AreEqual( evt->getClearColor() & 0xffffff, ptr[10] & 0xffffff );
            //}

            //evt->setClearColor( PixelColor( 255, 0, 128, 127 ) );
            //dx9->render();
            //{
            //    BackbufferHelper backbuffer( factory );
            //    NxU32 * const ptr = backbuffer.getBitPointer();
            //    Assert::IsTrue( NULL != ptr );
            //    Assert::AreEqual( evt->getClearColor() & 0xffffff, ptr[10] & 0xffffff );
            //}
        };
	};
}
