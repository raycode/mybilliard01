#include "stdafx.h"
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
        RenderWin32DX9 * dx9;
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
            dx9 = new RenderWin32DX9Imp();
            dx9->addRenderEventListener( evt );
        };

        [TestCleanup()]
        void MyTestCleanup() {
            Assert::IsTrue( evtSMC->isStateCorrectSoFar() );
            Assert::IsTrue( evtSMC->isStateCorrectToFinish() );
            delete evt;
            delete dx9;
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

            dx9->createDevice( true, 300, 300 );
            Assert::IsTrue( isState( 1, 1, 0, 0, 0, 0 ) );
            Assert::IsTrue( evtSMC->isStateCorrectSoFar() );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            dx9->destroyDevice();
            Assert::IsTrue( isState( 1, 1, 0, 0, 1, 1 ) );
        };

        [TestMethod]
        void StateCheck2_WithRender()
        {
            Assert::IsTrue( isState( 0, 0, 0, 0, 0, 0 ) );

            dx9->createDevice( false, 0, 0 );
            Assert::IsTrue( isState( 1, 1, 0, 0, 0, 0 ) );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            dx9->render();
            Assert::IsTrue( isState( 1, 1, 1, 1, 0, 0 ) );

            dx9->render();
            Assert::IsTrue( isState( 1, 1, 2, 2, 0, 0 ) );

            dx9->render();
            Assert::IsTrue( isState( 1, 1, 3, 3, 0, 0 ) );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );

            dx9->destroyDevice();
            Assert::IsTrue( isState( 1, 1, 3, 3, 1, 1 ) );
        };

    };
}
