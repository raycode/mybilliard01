#include "stdafx.h"
#include "test_dx9.h"

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
            delete dx9;
        };

    public:
        [TestMethod]
        void Constructor()
        {
        }

        [TestMethod]
        void CreateDevice1()
        {
            Assert::IsFalse( dx9->isDeviceCreated() );

            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );

            dx9->destroyDevice();
            Assert::IsFalse( dx9->isDeviceCreated() );
        }

        [TestMethod]
        void CreateDevice2()
        {
            CreateDevice1();
            CreateDevice1();
        }

        [TestMethod]
        void NoReleaseDevice()
        {
            Assert::IsFalse( dx9->isDeviceCreated() );
            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            delete dx9; // no release

            dx9 = new RenderWin32DX9Imp();
            Assert::IsFalse( dx9->isDeviceCreated() );
            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            dx9->destroyDevice();
            Assert::IsFalse( dx9->isDeviceCreated() );
        }

        [TestMethod]
        void CreateDeviceFromFullScreen()
        {
            Assert::IsFalse( dx9->isDeviceCreated() );

            Assert::IsTrue( dx9->createDevice( false, 0, 0 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );

            dx9->destroyDevice();
            Assert::IsFalse( dx9->isDeviceCreated() );
        }

        [TestMethod]
        void GetNativeDevice()
        {
            Assert::IsTrue( NULL == dx9->getD3D9Device() );

            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( NULL != dx9->getD3D9Device() );

            dx9->destroyDevice();
            Assert::IsTrue( NULL == dx9->getD3D9Device() );
        }

        [TestMethod]
        void AdjustCreatedDevice()
        {
            Assert::IsFalse( dx9->isDeviceCreated() );

            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            void * const nativeDevice = dx9->getD3D9Device();

            Assert::IsTrue( dx9->createDevice( false, 0, 0 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            Assert::IsTrue( dx9->getD3D9Device() == nativeDevice );

            dx9->destroyDevice();
            Assert::IsFalse( dx9->isDeviceCreated() );
            Assert::IsTrue( NULL == dx9->getD3D9Device() );
        }

        [TestMethod]
        void IsWindowed()
        {
            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isWindowed() );
            dx9->destroyDevice();
            dx9->isWindowed(); // after device released.
        }

        [TestMethod]
        void IsWindowed_StartFromFullScreen()
        {
            Assert::IsTrue( dx9->createDevice( false, 0, 0 ) );
            Assert::IsFalse( dx9->isWindowed() );
            dx9->destroyDevice();
            dx9->isWindowed(); // after device released.
        }

        [TestMethod]
        void ToggleFullScreen()
        {
            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isWindowed() );
            dx9->toggleFullScreen();
            Assert::IsFalse( dx9->isWindowed() );
            dx9->toggleFullScreen();
            Assert::IsTrue( dx9->isWindowed() );
        }

        [TestMethod]
        void ToggleFullScreen_StartFromFullScreen()
        {
            Assert::IsTrue( dx9->createDevice( false, 0, 0 ) );
            Assert::IsFalse( dx9->isWindowed() );
            dx9->toggleFullScreen();
            Assert::IsTrue( dx9->isWindowed() );
            dx9->toggleFullScreen();
            Assert::IsFalse( dx9->isWindowed() );
        }

    };
}
