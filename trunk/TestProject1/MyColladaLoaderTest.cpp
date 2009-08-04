#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestProject
{
	[TestClass]
	public ref class MyColladaLoaderTest
	{
	public: 

        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext)
        {};
        
        [ClassCleanup()]
        static void MyClassCleanup()
        {};
        
        [TestInitialize()]
        void MyTestInitialize()
        {};
        
        [TestCleanup()]
        void MyTestCleanup()
        {};

        [TestMethod]
        void VisualAssetFilename()
        {
            const wstring filename = ConstString::colladaVisualAssetFilename();
            Assert::IsFalse( filename.empty() );
            Assert::IsTrue( filename.find_last_of( L".dae" ) > 0u );
        }

        [TestMethod]
        void DllLoading()
        {
            DAE * dae = new DAE();
            Assert::IsTrue( NULL != dae );
            delete dae;
        }

        [TestMethod]
		void Constructor()
		{
            const wstring filename = ConstString::colladaVisualAssetFilename();

            MyColladaLoader loader( filename );
            //Assert::AreEqual( gcnew String( filename.c_str() ), gcnew String( loader.filename_.c_str() ) );
		};
	};
}
