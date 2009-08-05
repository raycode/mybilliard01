#include "stdafx.h"
#include "MyTestingUtility.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace MyTestingUtility;

//namespace TestProject1
//{
	[TestClass]
	public ref class MyColladaLoaderTest
	{
    private:
        static TestContext^ testContext_;

	public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext)
        {
            testContext_ = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize()
        {
            setCurrentDirectory( testContext_ );
        };

        [TestMethod]
        void CheckVisualAssetFilename()
        {
            const wstring filename = ConstString::colladaVisualAssetFilename();
            Assert::IsFalse( filename.empty() );
            Assert::IsTrue( filename.find_last_of( L".dae" ) > 0u );
        }

        [TestMethod]
        void FindVisualAssetFile()
        {
            const wstring assetFilename = ConstString::colladaVisualAssetFilename();
            const wstring filename = getDeployedFilename( assetFilename );
            Assert::IsTrue( isFileExist( filename ), gcnew String( filename.c_str() ) + " is not found." );
        }

        [TestMethod]
        void LoadColladaDLL()
        {
            DAE * dae = new DAE();
            Assert::IsTrue( NULL != dae );
            delete dae;
        }

        [TestMethod]
		void CreateColladaLoader()
		{
            const wstring filename = getDeployedFilename( ConstString::colladaVisualAssetFilename() );

            MyColladaLoader loader( filename );
            //Assert::AreEqual( gcnew String( filename.c_str() ), gcnew String( loader.filename_.c_str() ) );
		};

        [TestMethod]
        void CheckScene()
        {
            MyColladaLoader loader( getDeployedFilename( ConstString::colladaVisualAssetFilename() ) );

            //loader.getScene();
            //Assert::AreEqual( 1u, )
        }

        [TestMethod]
        void CheckVisualScenes()
        {
            MyColladaLoader loader( getDeployedFilename( ConstString::colladaVisualAssetFilename() ) );
        }

        [TestMethod]
        void CheckVisualSceneNodes()
        {
            //array< String^ >^ names = { L"Sphere01", L"Box01" };

            MyColladaLoader loader( getDeployedFilename( ConstString::colladaVisualAssetFilename() ) );
        }

        [TestMethod]
        void CheckGeometries()
        {
            MyColladaLoader loader( getDeployedFilename( ConstString::colladaVisualAssetFilename() ) );
        }
	};
//}
