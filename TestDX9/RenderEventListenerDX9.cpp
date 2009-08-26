#include "stdafx.h"
#include "test_dx9.h"
#include "RenderEventListenerDX9_DummyRenderListener.h"
#include "RenderListenerSMC.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace smc;
 

namespace TestDX9
{
	[TestClass]
	public ref class RenderEventListenerDX9
	{
    private:
        static TestContext^ testContextInstance;

    private:
        RenderWin32DX9 * render;
        RenderEventListener * evt;
        RenderListenerSMC * evtSMC;

    public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize() {
            evt = evtSMC = new RenderListenerSMC();
            render = new RenderWin32DX9Imp();
            render->addRenderEventListener( evt );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            Assert::IsTrue( evtSMC->isStateCorrectSoFar() );
            Assert::IsTrue( evtSMC->isStateCorrectToFinish() );
            delete evt;
            delete render;
        };

        bool isState( int init, int reset, int update, int display, int lost, int destroy ) {
            return
                init == evtSMC->countInit_ &&
                reset == evtSMC->countReset_ &&
                update == evtSMC->countUpdate_ &&
                display == evtSMC->countDisplay_ &&
                lost == evtSMC->countLost_ &&
                destroy == evtSMC->countDestroy_;
        }

    public:
		[TestMethod]
		void Construction()
		{
		};


        [TestMethod]
        void StateCheck1()
        {
            Assert::IsTrue( isState( 0, 0, 0, 0, 0, 0 ) );

            render->createDevice( true, 300, 300 );
            Assert::IsTrue( isState( 1, 1, 0, 0, 0, 0 ) );
            Assert::IsTrue( evtSMC->isStateCorrectSoFar() );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            render->destroyDevice();
            Assert::IsTrue( isState( 1, 1, 0, 0, 1, 1 ) );
        };

        [TestMethod]
        void StateCheck2_WithRender()
        {
            Assert::IsTrue( isState( 0, 0, 0, 0, 0, 0 ) );

            render->createDevice( false, 0, 0 );
            Assert::IsTrue( isState( 1, 1, 0, 0, 0, 0 ) );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            render->renderOneFrame();
            Assert::IsTrue( isState( 1, 1, 1, 1, 0, 0 ) );

            render->renderOneFrame();
            Assert::IsTrue( isState( 1, 1, 2, 2, 0, 0 ) );

            render->renderOneFrame();
            Assert::IsTrue( isState( 1, 1, 3, 3, 0, 0 ) );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            render->destroyDevice();
            Assert::IsTrue( isState( 1, 1, 3, 3, 1, 1 ) );
        };

    };
}
