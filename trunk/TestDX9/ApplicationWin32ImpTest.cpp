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


struct ApplicationWin32Imp::TestingBackdoor {
    static bool getWindowedMode( ApplicationWin32Imp * app ) {
        return app->bWindowedMode_;
    }
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
        void DefaultWindowedMode() {
            NullRender nullRender;
            Assert::IsFalse( nullRender.isDeviceCreated() );
            Assert::IsTrue( ApplicationWin32Imp::TestingBackdoor::getWindowedMode( appImp ) );
            Assert::IsTrue( app->isWindowedMode() );
        }

        [TestMethod]
        void WindowedMode() {
            app->setWindowedMode( false );
            Assert::AreEqual( false, app->isWindowedMode() );
        }

        [TestMethod]
        void DefaultWindowTitle() {
            Assert::IsTrue( app->getScreenTitle() == L"");
        }

        [TestMethod]
        void WindowTitle() {
            app->setScreenTitle( L"My new title" );
            Assert::IsTrue( app->getScreenTitle() == L"My new title" );
        }
            //InputListenerImp * inputListener = new InputListenerImp( renderEvent );

            //ApplicationWin32 * app = new ApplicationWin32Imp();
            //app->setRender( render );
            //app->addKeyboardListener( inputListener );
            //app->addMouseListener( inputListener );
            //app->addWin32MessageListener( inputListener );
            //app->setScreenTitle( ConstString::windowTitle() );
            //app->start();

            //delete app;
            //delete inputListener;
	};
}
