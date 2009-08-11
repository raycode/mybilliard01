#include "stdafx.h"
#include "../render_win32/my_render_win32_imp.h"
#include "../render_win32/my_render_win32_dx9_imp.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace std;
using namespace my_render;
using namespace my_render_win32;
using namespace my_render_win32_dx9;

using namespace my_render_imp;
using namespace my_render_win32_imp;
using namespace my_render_win32_dx9_imp;


#define PRIVATE_METHOD( methodName ) ApplicationWin32Imp::TestingBackdoor::methodName
#define ACCESS_0( returnType, methodName ) static returnType methodName( ApplicationWin32Imp * app ) { return app->methodName(); }
#define ACCESS_0_VOID( methodName ) static void methodName( ApplicationWin32Imp * app ) { app->methodName(); }

struct ApplicationWin32Imp::TestingBackdoor {
    ACCESS_0( bool, createWindow );
    ACCESS_0_VOID( destroyWindow );
};


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
		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		[ClassInitialize()]
		static void MyClassInitialize(TestContext^ testContext) {
            testContextInstance = testContext;
        };
		
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		[TestInitialize()]
		void MyTestInitialize() {
            appImp = new ApplicationWin32Imp();
            app = appImp;
        };
		
		//Use TestCleanup to run code after each test has run
		[TestCleanup()]
		void MyTestCleanup() {
            delete app;
        };
		
		#pragma endregion 

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
            NullRender nullRender;
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
            Assert::IsTrue( app->getScreenTitle() == L"" );
            Assert::IsTrue( app->getScreenTitle().empty() );
        }

        [TestMethod]
        void WindowTitle() {
            app->setScreenTitle( L"My new title" );
            Assert::IsTrue( app->getScreenTitle() == L"My new title" );
        }

        [TestMethod]
        void SetRender() {
            Render * const defaultRender = app->getRender();
            Assert::IsTrue( NULL != defaultRender );

            NullRender nullRender;
            Assert::IsFalse( app->setRender( &nullRender ) );
            Assert::IsTrue( app->getRender() != &nullRender );
            Assert::IsTrue( app->getRender() == defaultRender );

            NullRenderWin32 nullRenderWin32;
            Assert::IsTrue( app->setRender( &nullRenderWin32 ) );
            Assert::IsTrue( app->getRender() == &nullRenderWin32 );
        }

        [TestMethod]
        void DefaultGetHWND() {
            Assert::IsTrue( app->getHWND() == NULL );
        }

        [TestMethod]
        void CreateAndDestroyWindow1() {
            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );
            PRIVATE_METHOD( destroyWindow )( appImp );
        }

        [TestMethod]
        void CreateAndDestroyWindow2() {
            PRIVATE_METHOD( destroyWindow )( appImp ); // before creation

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );
            const HWND hWnd = appImp->getHWND();
            Assert::IsTrue( hWnd != NULL );

            Assert::IsFalse( PRIVATE_METHOD( createWindow )( appImp ) ); // double creation
            Assert::IsTrue( hWnd == appImp->getHWND() );

            PRIVATE_METHOD( destroyWindow )( appImp );
        }

        [TestMethod]
        void ScreenWidthAndHeight2() {
            // before creation
            Assert::AreEqual( 640, appImp->getScreenWidth() );
            Assert::AreEqual( 480, appImp->getScreenHeight() );

            Assert::IsTrue( PRIVATE_METHOD( createWindow )( appImp ) );

            // after creation
            Assert::AreEqual( 640, appImp->getScreenWidth() );
            Assert::AreEqual( 480, appImp->getScreenHeight() );

            // actual size
            RECT rt;
            ::GetWindowRect( appImp->getHWND(), &rt );
            const int width = rt.right - rt.left;
            const int height = rt.bottom - rt.top;
            Assert::AreEqual( 640, width );
            Assert::AreEqual( 480, height );

            PRIVATE_METHOD( destroyWindow )( appImp );

            // after destroy
            Assert::AreEqual( 640, appImp->getScreenWidth() );
            Assert::AreEqual( 480, appImp->getScreenHeight() );
        }

    };
}
