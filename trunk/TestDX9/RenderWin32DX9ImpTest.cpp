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
            delete dx9Imp; // no release

            dx9Imp = new RenderWin32DX9Imp();
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
            Assert::IsTrue( NULL == dx9->getNativeDevice() );

            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( NULL != dx9->getNativeDevice() );

            dx9->destroyDevice();
            Assert::IsTrue( NULL == dx9->getNativeDevice() );
        }

        [TestMethod]
        void AdjustCreatedDevice()
        {
            Assert::IsFalse( dx9->isDeviceCreated() );

            Assert::IsTrue( dx9->createDevice( true, 320, 240 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            void * const nativeDevice = dx9->getNativeDevice();

            Assert::IsTrue( dx9->createDevice( false, 0, 0 ) );
            Assert::IsTrue( dx9->isDeviceCreated() );
            Assert::IsTrue( dx9->getNativeDevice() == nativeDevice );

            dx9->destroyDevice();
            Assert::IsFalse( dx9->isDeviceCreated() );
            Assert::IsTrue( NULL == dx9->getNativeDevice() );
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

        [TestMethod]
        void UpAxis()
        {
            dx9->setUpAxis( UPAXISTYPE_Y_UP );
            Assert::IsTrue( UPAXISTYPE_Y_UP == dx9->getUpAxis() );

            dx9->setUpAxis(UPAXISTYPE_Z_UP);
            Assert::IsTrue( UPAXISTYPE_Z_UP == dx9->getUpAxis() );
        }
    };
}
