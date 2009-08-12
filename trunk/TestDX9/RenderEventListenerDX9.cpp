#include "stdafx.h"
#include "RenderEventListenerDX9_DummyEventListener.h"
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

    public:
		[TestMethod]
		void Construction()
		{
		};


        [TestMethod]
        void RenderListenerState()
        {
            dx9->createDevice( true, 300, 300 );
            Assert::IsTrue( evtSMC->isStateCorrectSoFar() );
            Assert::IsFalse( evtSMC->isStateCorrectToFinish() );
            dx9->destroyDevice();
        };

    };
}
