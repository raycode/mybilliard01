#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

class RenderListener_clear : public NullRenderEventListener {
public:
    virtual void display( Render * render ) OVERRIDE {
//        render->clear( ERenderClear_TARGET, NxU32( 0u, ) );
    }
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
        };

        [TestCleanup()]
        void MyTestCleanup() {
            delete evt;
            delete dx9;
        };

    public:
		[TestMethod]
		void TestMethod1()
		{
            evt = new RenderListener_clear();
            dx9->addRenderEventListener( evt );
		};
	};
}
