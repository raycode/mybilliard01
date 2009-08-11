#include "stdafx.h"
#include "../mybilliard01/my_render_win32_imp.h"
#include "../mybilliard01/my_render_win32_dx9_imp.h"

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
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestMethod1()
		{
            //InputListenerImp * inputListener = new InputListenerImp( renderEvent );

            ApplicationWin32 * app = new ApplicationWin32Imp();
            //app->setRender( render );
            //app->addKeyboardListener( inputListener );
            //app->addMouseListener( inputListener );
            //app->addWin32MessageListener( inputListener );
            //app->setScreenWidth( 640 );
            //app->setScreenHeight( 480 );
            //app->setWindowedMode( true );
            //app->setScreenTitle( ConstString::windowTitle() );
            //app->start();

            delete app;
            //delete inputListener;
		};
	};
}
