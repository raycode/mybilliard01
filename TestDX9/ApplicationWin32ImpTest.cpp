#include "stdafx.h"
#include "test_dx9.h"
#include "ApplicationWin32Imp_Backdoor.hpp"
#include "ApplicationWin32ImpTest_DummyRenderWin32.hpp"
#include "ApplicationWin32ImpTest_DummyKeyboardListener.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;


namespace TestDX9
{
	[TestClass]
	public ref class ApplicationWin32ImpTest
	{
	private:
		static TestContext^ testContextInstance;

    private:
        ApplicationWin32 * app;
        ApplicationWin32Imp * appImp;

	public: 
		[ClassInitialize()]
		static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };
		
		[TestInitialize()]
		void MyTestInitialize() {
            appImp = new ApplicationWin32Imp();
            app = appImp;
        };
		
		[TestCleanup()]
		void MyTestCleanup() {
            delete app;
        };
		

    public:
		[TestMethod]
		void Constructor()
		{
        }

        [TestMethod]
        void DefaultScreenWidthAndHeight() {
            Assert::AreEqual( 640, app->getScreenWidth() );
            Assert::AreEqual( 480, app->getScreenHeight() );
        }
        
        [TestMethod]
        void ScreenWidthAndHeight() {
            app->setScreenWidth( 641 );
            app->setScreenHeight( 481 );

            Assert::AreEqual( 641, app->getScreenWidth() );
            Assert::AreEqual( 481, app->getScreenHeight() );
        }

        [TestMethod]
        void DefaultScreenXY() {
            assertTrue( app->getScreenX() >= 0 );
            assertTrue( app->getScreenY() >= 0 );
            assertTrue( app->getScreenX() <= 3000 );
            assertTrue( app->getScreenY() <= 2000 );
        }

        [TestMethod]
        void ScreenXY() {
            app->setScreenX( 123 );
            app->setScreenY( 32 );

            assertTrue( app->getScreenX() == 123 );
            assertTrue( app->getScreenY() >= 32 );
        }

        [TestMethod]
        void DefaultWindowedMode() {
            RenderWin32Null nullRender;
            Assert::IsFalse( nullRender.isDeviceCreated() );
            assertTrue( app->isWindowedMode() );
        }

        [TestMethod]
        void WindowedMode() {
            app->setWindowedMode( false );
            Assert::AreEqual( false, app->isWindowedMode() );
        }

        [TestMethod]
        void DefaultWindowTitle() {
            assertStrEquals( L"", app->getScreenTitle() );
        }

        [TestMethod]
        void WindowTitle() {
            app->setScreenTitle( L"My new title" );
            assertStrEquals( L"My new title", app->getScreenTitle() );
        }

        [TestMethod]
        void SetRender() {
            Render * const defaultRender = app->getRender();
            assertTrue( NULL != defaultRender );

            RenderNull nullRender;
            Assert::IsFalse( app->setRender( &nullRender ) );
            assertTrue( app->getRender() != &nullRender );
            assertTrue( app->getRender() == defaultRender );

            RenderWin32Null nullRenderWin32;
            assertTrue( app->setRender( &nullRenderWin32 ) );
            assertTrue( app->getRender() == &nullRenderWin32 );
        }

        [TestMethod]
        void DefaultGetHWND() {
            assertTrue( app->getHWND() == NULL );
        }

        [TestMethod]
        void CreateAndDestroyWindow1() {
            Assert::IsFalse( PRIVATE_METHOD( ApplicationWin32Imp, isWindowCreated )( appImp ) );
            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) );
            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, isWindowCreated )( appImp ) );
            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );
            Assert::IsFalse( PRIVATE_METHOD( ApplicationWin32Imp, isWindowCreated )( appImp ) );
        }

        [TestMethod]
        void CreateAndDestroyWindow2() {
            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp ); // before creation

            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) );
            const HWND hWnd = app->getHWND();
            assertTrue( hWnd != NULL );

            Assert::IsFalse( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) ); // double creation
            assertTrue( hWnd == app->getHWND() );

            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );
        }

        [TestMethod]
        void ScreenWidthAndHeight2() {
            // before creation
            Assert::AreEqual( 640, app->getScreenWidth() );
            Assert::AreEqual( 480, app->getScreenHeight() );

            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( 640, app->getScreenWidth() );
            Assert::AreEqual( 480, app->getScreenHeight() );

            // actual size
            RECT rt;
            ::GetWindowRect( app->getHWND(), &rt );
            const int width = rt.right - rt.left;
            const int height = rt.bottom - rt.top;
            Assert::AreEqual( 640, width );
            Assert::AreEqual( 480, height );

            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );

            // after destroy
            Assert::AreEqual( 640, app->getScreenWidth() );
            Assert::AreEqual( 480, app->getScreenHeight() );
        }

        [TestMethod]
        void ScreenXY2() {
            app->setScreenX( 11 );
            app->setScreenY( 12 );

            // before creation
            Assert::AreEqual( 11, app->getScreenX() );
            Assert::AreEqual( 12, app->getScreenY() );

            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( 11, app->getScreenX() );
            Assert::AreEqual( 12, app->getScreenY() );

            // actual position
            RECT rt;
            ::GetWindowRect( app->getHWND(), &rt );
            Assert::AreEqual( 11, rt.left );
            Assert::AreEqual( 12, rt.top );

            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );

            // after destroy
            Assert::AreEqual( 11, app->getScreenX() );
            Assert::AreEqual( 12, app->getScreenY() );
        }

        [TestMethod]
        void Title2() {
            const wstring longTitle = L"abcdefghijklmnop with space and symbols !?";
            app->setScreenTitle( longTitle );

            // before creation
            Assert::AreEqual( getString( app->getScreenTitle() ), getString( longTitle ) );

            assertTrue( PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( getString( app->getScreenTitle() ), getString( longTitle ) );

            // actual title
            wchar_t szTmp[256];
            GetWindowText( appImp->getHWND(), szTmp, 256 );
            Assert::AreEqual( getString( longTitle ), getString( szTmp ) );

            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );

            // after destroy
            Assert::AreEqual( getString( app->getScreenTitle() ), getString( longTitle ) );
        }

        [TestMethod, Timeout(10000)]
        void MainLoop() {
            DummyRenderWin32_ApplicationWin32Imp dummyRender;
            app->setRender( &dummyRender );
            assertTrue( &dummyRender == app->getRender() );

            PRIVATE_METHOD( ApplicationWin32Imp, createWindow )( appImp );
            PRIVATE_METHOD( ApplicationWin32Imp, mainLoop )( appImp );
            PRIVATE_METHOD( ApplicationWin32Imp, destroyWindow )( appImp );
        }

        [TestMethod, Timeout(10000)]
        void Start() {
            DummyRenderWin32_ApplicationWin32Imp dummyRender;
            app->setRender( &dummyRender );
            app->start();
        }

        [TestMethod]
        void AddKeyboardListener() {
            DummyKeyboardListener_ApplicationWin32Imp keyListener;
            app->addKeyboardListener( &keyListener );

            keyListener.appendExpectingKey( VK_RIGHT, true, false );
            PRIVATE_METHOD( ApplicationWin32Imp, MsgProcKeyboard )( appImp, NULL, WM_KEYDOWN, VK_RIGHT, 0 );

            assertTrue( keyListener.isAllKeyRecieved() );
        }

        [TestMethod]
        void AddMouseListener() {
        }

        [TestMethod]
        void AddWin32MessageListener() {
        }

        //void setMinimized( bool );
        //void setMaximized( bool );
        //void setSizeInMove( bool );
        //bool isMinimized();
        //bool isMaximized();
        //bool isSizeInMove();

        [TestMethod]
        void MessageProc() {
        }

    };
}
