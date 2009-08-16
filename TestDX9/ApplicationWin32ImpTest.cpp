#include "stdafx.h"
#include "ApplicationWin32ImpTest_Backdoor.hpp"
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
            Assert::IsTrue( app->getScreenX() >= 0 );
            Assert::IsTrue( app->getScreenY() >= 0 );
            Assert::IsTrue( app->getScreenX() <= 3000 );
            Assert::IsTrue( app->getScreenY() <= 2000 );
        }

        [TestMethod]
        void ScreenXY() {
            app->setScreenX( 123 );
            app->setScreenY( 32 );

            Assert::IsTrue( app->getScreenX() == 123 );
            Assert::IsTrue( app->getScreenY() >= 32 );
        }

        [TestMethod]
        void DefaultWindowedMode() {
            RenderWin32Null nullRender;
            Assert::IsFalse( nullRender.isDeviceCreated() );
            Assert::IsTrue( app->isWindowedMode() );
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
            Assert::IsTrue( NULL != defaultRender );

            RenderNull nullRender;
            Assert::IsFalse( app->setRender( &nullRender ) );
            Assert::IsTrue( app->getRender() != &nullRender );
            Assert::IsTrue( app->getRender() == defaultRender );

            RenderWin32Null nullRenderWin32;
            Assert::IsTrue( app->setRender( &nullRenderWin32 ) );
            Assert::IsTrue( app->getRender() == &nullRenderWin32 );
        }

        [TestMethod]
        void DefaultGetHWND() {
            Assert::IsTrue( app->getHWND() == NULL );
        }

        [TestMethod]
        void CreateAndDestroyWindow1() {
            Assert::IsFalse( PRIVATE_METHOD( isWindowCreated )( appImp ) );
            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );
            Assert::IsTrue( PRIVATE_METHOD( isWindowCreated )( appImp ) );
            PRIVATE_METHOD( destroyWindow )( appImp );
            Assert::IsFalse( PRIVATE_METHOD( isWindowCreated )( appImp ) );
        }

        [TestMethod]
        void CreateAndDestroyWindow2() {
            PRIVATE_METHOD( destroyWindow )( appImp ); // before creation

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );
            const HWND hWnd = app->getHWND();
            Assert::IsTrue( hWnd != NULL );

            Assert::IsFalse( PRIVATE_METHOD( createWindow )( appImp ) ); // double creation
            Assert::IsTrue( hWnd == app->getHWND() );

            PRIVATE_METHOD( destroyWindow )( appImp );
        }

        [TestMethod]
        void ScreenWidthAndHeight2() {
            // before creation
            Assert::AreEqual( 640, app->getScreenWidth() );
            Assert::AreEqual( 480, app->getScreenHeight() );

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );

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

            PRIVATE_METHOD( destroyWindow )( appImp );

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

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( 11, app->getScreenX() );
            Assert::AreEqual( 12, app->getScreenY() );

            // actual position
            RECT rt;
            ::GetWindowRect( app->getHWND(), &rt );
            Assert::AreEqual( 11, rt.left );
            Assert::AreEqual( 12, rt.top );

            PRIVATE_METHOD( destroyWindow )( appImp );

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

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( getString( app->getScreenTitle() ), getString( longTitle ) );

            // actual title
            wchar_t szTmp[256];
            GetWindowText( appImp->getHWND(), szTmp, 256 );
            Assert::AreEqual( getString( longTitle ), getString( szTmp ) );

            PRIVATE_METHOD( destroyWindow )( appImp );

            // after destroy
            Assert::AreEqual( getString( app->getScreenTitle() ), getString( longTitle ) );
        }

        [TestMethod, Timeout(10000)]
        void MainLoop() {
            DummyRenderWin32_ApplicationWin32Imp dummyRender;
            app->setRender( &dummyRender );
            Assert::IsTrue( &dummyRender == app->getRender() );

            PRIVATE_METHOD( createWindow )( appImp );
            PRIVATE_METHOD( mainLoop )( appImp );
            PRIVATE_METHOD( destroyWindow )( appImp );
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
            PRIVATE_METHOD( MsgProcKeyboard )( appImp, NULL, WM_KEYDOWN, VK_RIGHT, 0 );

            Assert::IsTrue( keyListener.isAllKeyRecieved() );
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
