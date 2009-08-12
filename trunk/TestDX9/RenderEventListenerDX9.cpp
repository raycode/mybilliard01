#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


class DummyEventListener_RenderWin32DX9Imp : public NullRenderEventListener {
public:
    virtual void init( Render * render )
    {

    }

    virtual void displayReset( Render * render, int x, int y, int width, int height )
    {

    }

    virtual void update( float elapsedTime )
    {

    }

    virtual void display( Render * render )
    {


    }

    virtual void displayLost( Render * render )
    {


    }

    virtual void destroy( Render * render )
    {


    }

};


namespace TestDX9
{
	[TestClass]
	public ref class RenderEventListenerDX9
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
            evt = new DummyEventListener_RenderWin32DX9Imp();
            dx9->addRenderEventListener( evt );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            delete evt;
            delete dx9;
        };

    public:
		[TestMethod]
		void Construction()
		{
		};


    };
}
