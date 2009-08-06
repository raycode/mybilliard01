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

    static wstring getFilename() {
        return getDeployedFilename( ConstString::colladaVisualAssetFilename() );
    }

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
        const wstring filename = getFilename();
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
        MyColladaLoader loader( getFilename() );
	};

    [TestMethod]
    void CheckScene()
    {
        MyColladaLoader loader( getFilename() );

        domCOLLADA::domScene * const scene = loader.getCOLLADA()->getScene();
        Assert::IsTrue( NULL != scene );

        domInstanceWithExtraRef instance_visual_scene = scene->getInstance_visual_scene();
        Assert::IsTrue( NULL != instance_visual_scene );

        String^ url = gcnew String( convertString< wstring >( instance_visual_scene->getUrl().originalStr() ).c_str() );
        Assert::AreEqual( "#RootNode", url );
    }

    [TestMethod]
    void CheckVisualScenes()
    {
        MyColladaLoader loader( getFilename() );

        //daeElement * const vscene = loader.getVisualScene( L"#RootNode" );
        //Assert::IsTrue( NULL != vscene );
    }

    [TestMethod]
    void CheckVisualSceneNodes()
    {
        //array< String^ >^ names = { L"Sphere01", L"Box01" };

        MyColladaLoader loader( getFilename() );
    }

    [TestMethod]
    void CheckGeometries()
    {
        MyColladaLoader loader( getFilename() );
    }
};
//}
