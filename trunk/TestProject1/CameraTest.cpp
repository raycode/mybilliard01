#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

[TestClass]
public ref class CameraTest
{
private:
    static TestContext^ testContext_;
    SceneImp * scene;

    static wstring getDuckFilename() {
        return getDeployedFilename( L"asset\\duck.dae" );
    }

    static wstring getBallFilename() {
        return getDeployedFilename( L"asset\\1ball1box.dae" );
    }

public: 
    [ClassInitialize()]
    static void MyClassInitialize(TestContext^ testContext) {
        testContext_ = testContext;
    };

    [TestInitialize()]
    void MyTestInitialize() {
        setCurrentDirectory( testContext_ );
        scene = new SceneImp();
    };

    [TestCleanup()]
    void MyTestCleanup() {
        delete scene;
    };

public:
	[TestMethod]
	void FixtureOnly()
	{
	};

    [TestMethod]
    void LoadDuck()
    {
        assertTrue( scene->load( getDuckFilename() ) );
    };

    [TestMethod]
    void GetCamera()
    {
        assertTrue( scene->load( getDuckFilename() ) );
        assertEquals( 1u, scene->getNumberOfCamera() );

        Camera * const camera = scene->getCameraByIndex( 0 );
        assertNotNull( camera );
        assertStrEquals( L"cameraShape1", camera->getID() );
    }

    [TestMethod]
    void DefaultCamera()
    {
        assertTrue( scene->load( getBallFilename() ) );
        assertEquals( 1u, scene->getNumberOfCamera() );
    }

};
