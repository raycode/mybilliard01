#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

class RenderListener_clear : public NullRenderEventListener {
public:
    RenderListener_clear( NxU32 clearColor )
        : clearColor_( clearColor )
    {}

public:
    virtual void display( Render * render ) OVERRIDE {
        render->clear( ERenderClear_TARGET, clearColor_, 1.f, 0 );
    }

private:
    NxU32 clearColor_;
};


class Backbuffer {
public:
    NxU32 * getBitPointer() {
        return bitPointer;
    }

    Backbuffer( Render * render )
        : render_( render )
    {
        backbuffer_ = render->getBackBuffer( 0 );
        if( NULL == backbuffer_ ) throw exception();

        SurfaceLockedRect * const locked = backbuffer_->lockRect( SurfaceLock_READONLY );
        if( NULL == locked ) throw exception();

        bitPointer = (NxU32*) locked->getBitPointer();
    }

    ~Backbuffer() {
        render_->releaseSurface( backbuffer_ );        
    }

private:
    Render * render_;
    Surface * backbuffer_;
    NxU32 * bitPointer;
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
        RenderEventListener * evt;

    public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize() {
            dx9 = new RenderWin32DX9Imp();
            dx9->setBackbufferLockable( true );
            dx9->createDevice( true, 30, 30 );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            dx9->destroyDevice();
            delete evt;
            delete dx9;
        };

    public:
		[TestMethod]
		void TestMethod1()
		{
            evt = new RenderListener_clear( PixelColor( 1, 0, 0, 0 ) );
            dx9->addRenderEventListener( evt );
            dx9->render();

            {
                Backbuffer backbuffer( dx9 );
            //    NxU32 * const ptr = backbuffer.getBitPointer();
            //    Assert::IsTrue( NULL != ptr );

            //    Assert::AreEqual( 0u, ptr[0] );
            }
		};
	};
}
