#include "stdafx.h"
#include "RenderBufferFactoryDX9Test_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestDX9
{
	[TestClass]
	public ref class RenderBufferFactoryDX9Test_Effect
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

    public:
		[TestMethod]
		void TestMethod1()
		{
			//
			// TODO: Add test logic	here
			//
		};
	};
}
