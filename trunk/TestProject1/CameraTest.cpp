#include "stdafx.h"
#include "test_collada.h"

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
    void GetDefaultCamera()
    {
        assertTrue( scene->load( getBallFilename() ) );
        assertEquals( 1u, scene->getNumberOfCamera() );
        Camera * const camera = scene->getCameraByIndex( 0 );
        assertNotNull( camera );
    }

    [TestMethod]
    void GetCameraValueFromCollada()
    {
        assertTrue( scene->load( getDuckFilename() ) );
        Camera * const camera = scene->getCameraByIndex( 0 );
        assertNotNull( camera );

        assertTrue( camera->isPerspective() );
        assertFalse( camera->isOrthographic() );

        assertFloatEquals( 37.89f, camera->getPerspectiveCamera()->getYFov(), 0.1f );
        assertFloatEquals( 1.5f, camera->getPerspectiveCamera()->getAspect(), 0.1f );
        assertFloatEquals( 1.f, camera->getPerspectiveCamera()->getZNear(), 0.1f );
        assertFloatEquals( 10000.f, camera->getPerspectiveCamera()->getZFar(), 10.f );
    }

    [TestMethod]
    void GetCameraValueFromDefault()
    {
        assertTrue( scene->load( getBallFilename() ) );
        Camera * const camera = scene->getCameraByIndex( 0 );
        assertNotNull( camera );

        assertTrue( camera->isPerspective() );
        assertFalse( camera->isOrthographic() );

        assertFloatEquals( 36.f, camera->getPerspectiveCamera()->getYFov(), 0.1f );
        assertFloatEquals( 1.8f, camera->getPerspectiveCamera()->getAspect(), 0.1f );
        assertFloatEquals( 0.01f, camera->getPerspectiveCamera()->getZNear(), 0.1f );
        assertFloatEquals( 1000.f, camera->getPerspectiveCamera()->getZFar(), 10.f );
    }

    [TestMethod]
    void GetPerspectiveProjectionMatirxRH()
    {
        CameraImp camera;
        assertTrue( camera.isPerspective() );

        D3DXMATRIX expected;
        D3DXMATRIX rst;
        camera.getProjectionMatrix44( (float*) (rst.m), true, false );
        assertTrue( TRUE == (expected != rst) );

        //const float yFov = camera.getPerspectiveCamera()->getYFov();
        const float aspect = camera.getPerspectiveCamera()->getAspect();
        const float zn = camera.getPerspectiveCamera()->getZNear();
        const float zf = camera.getPerspectiveCamera()->getZFar();
        D3DXMatrixPerspectiveFovRH( &expected, D3DX_PI / 5.f, aspect, zn, zf );

        assertFloatEquals( expected( 1, 1 ), rst( 1, 1 ), 0.001f ); // yScale

        assertFloatEquals( expected( 0, 0 ), rst( 0, 0 ), 0.001f ); // xScale
        assertFloatEquals( expected( 1, 0 ), rst( 1, 0 ), 0.001f );
        assertFloatEquals( expected( 2, 0 ), rst( 2, 0 ), 0.001f );
        assertFloatEquals( expected( 3, 0 ), rst( 3, 0 ), 0.001f );

        assertFloatEquals( expected( 0, 1 ), rst( 0, 1 ), 0.001f );
        assertFloatEquals( expected( 1, 1 ), rst( 1, 1 ), 0.001f );
        assertFloatEquals( expected( 2, 1 ), rst( 2, 1 ), 0.001f );
        assertFloatEquals( expected( 3, 1 ), rst( 3, 1 ), 0.001f );

        assertFloatEquals( expected( 0, 2 ), rst( 0, 2 ), 0.001f );
        assertFloatEquals( expected( 1, 2 ), rst( 1, 2 ), 0.001f );
        assertFloatEquals( expected( 2, 2 ), rst( 2, 2 ), 0.001f );
        assertFloatEquals( expected( 3, 2 ), rst( 3, 2 ), 0.001f );

        assertFloatEquals( expected( 0, 3 ), rst( 0, 3 ), 0.001f );
        assertFloatEquals( expected( 1, 3 ), rst( 1, 3 ), 0.001f );
        assertFloatEquals( expected( 2, 3 ), rst( 2, 3 ), 0.001f );
        assertFloatEquals( expected( 3, 3 ), rst( 3, 3 ), 0.001f );

        //assertTrue( TRUE == (expected == rst) );
    }
};
