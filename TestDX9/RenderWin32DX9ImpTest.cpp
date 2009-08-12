#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace TestDX9
{
	[TestClass]
	public ref class RenderWin32DX9ImpTest
	{
    private:
        static TestContext^ testContextInstance;

    private:
        RenderWin32DX9 * dx9;
        RenderWin32DX9Imp * dx9Imp;

	public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize() {
            dx9Imp = new RenderWin32DX9Imp();
            dx9 = dx9Imp;
        };

        [TestCleanup()]
        void MyTestCleanup() {
            delete dx9Imp;
        };

    public:
        [TestMethod]
        void Constructor()
        {
        }

	};
}
