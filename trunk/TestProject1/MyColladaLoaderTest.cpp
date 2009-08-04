#include "stdafx.h"
using namespace std;
using namespace billiard;

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestProject
{
	[TestClass]
	public ref class MyColladaLoaderTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ testContext
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

		[TestMethod]
		void TestMethod1()
		{
            const wstring filename = ConstString::colladaVisualAssetFilename();
            MyColladaLoader loader( filename );
            Assert::AreEqual( gcnew String( filename.c_str() ), gcnew String( loader.filename_.c_str() ) );
		};
	};
}
