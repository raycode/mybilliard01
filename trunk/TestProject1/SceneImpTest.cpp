#include "stdafx.h"
#include "SceneImp_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

struct DummyNode_forDisplayTest : public NodeNull {
    DummyNode_forDisplayTest() : counter_( 0 ) {}
    size_t counter_;
    virtual void display( Render * ) OVERRIDE {
        ++counter_;
    }
};

[TestClass]
public ref class SceneImpTest
{
private:
    static TestContext^ testContext_;
    SceneImp * scene;

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

    static wstring getFilename() {
        return getDeployedFilename( L"asset\\1ball1box.dae" );
    }

public:
    [TestMethod]
    void ConstructScene() {
        assertTrue( NULL != scene );
    }

    [TestMethod]
    void loadCollada() {
        const bool succeed1 = scene->load( getFilename() );
        assertTrue( succeed1 );
    }

    [TestMethod]
    void loadCollada_wrongfile() {
        const bool fail1 = scene->load( L"NoFile.dae" );
        assertFalse( fail1 );
    }

    [TestMethod]
    void VisualSceneID() {
        assertTrue( scene->load( getFilename() ) );

        vector< wstring > id_array = scene->getVisualSceneIDs();
        assertEquals( 1u, id_array.size() );
        assertStrEquals( L"RootNode", id_array[0] );
    }

    [TestMethod]
    void DefaultVisualSceneID() {
        assertTrue( scene->load( getFilename() ) );
        assertTrue( scene->hasDefaultVisualSceneID() );
        assertStrEquals( L"RootNode", scene->getDefaultVisualSceneID() );
    }

    [TestMethod]
    void loadCollada_severalTimes() {
        assertTrue( scene->load( getFilename() ) );
        assertEquals( 1u, scene->getVisualSceneIDs().size() );

        assertTrue( scene->load( L"./" + getFilename() ) );
        assertEquals( 1u, scene->getVisualSceneIDs().size() );

        assertTrue( scene->load( L".\\" + getFilename() ) );
        assertEquals( 1u, scene->getVisualSceneIDs().size() );

        assertFalse( scene->load( L"NoFile.dae" ) );
    }

    [TestMethod]
    void GetVisualSceneIDs() {
        assertTrue( scene->load( getFilename() ) );
        assertStrEquals( scene->getCurrentVisualSceneID(), scene->getDefaultVisualSceneID() );

        scene->setCurrentVisualScene( scene->getDefaultVisualSceneID() );
        assertStrEquals( scene->getCurrentVisualSceneID(), scene->getDefaultVisualSceneID() );
    }

    [TestMethod]
    void StoreFilename1() {
        PRIVATE_METHOD( SceneImp, storeFilename )( scene, L"ABC.dat" );
        assertStrEquals( L"ABC.dat", PRIVATE_METHOD( SceneImp, filename_ )( scene ) );
        assertStrEquals( L"", PRIVATE_METHOD( SceneImp, pathname_ )( scene ) );
    }

    [TestMethod]
    void StoreFilename2() {
        PRIVATE_METHOD( SceneImp, storeFilename )( scene, L"c:\\ABC.dat" );
        assertStrEquals( L"ABC.dat", PRIVATE_METHOD( SceneImp, filename_ )( scene ) );
        assertStrEquals( L"c:", PRIVATE_METHOD( SceneImp, pathname_ )( scene ) );
    }

    [TestMethod]
    void StoreFilename3() {
        PRIVATE_METHOD( SceneImp, storeFilename )( scene, L"c:\\dir/ABC.dat" );
        assertStrEquals( L"ABC.dat", PRIVATE_METHOD( SceneImp, filename_ )( scene ) );
        assertStrEquals( L"c:\\dir", PRIVATE_METHOD( SceneImp, pathname_ )( scene ) );
    }

    [TestMethod]
    void StoreFilename4() {
        PRIVATE_METHOD( SceneImp, storeFilename )( scene, L"c:\\dir1/dir2\\ABC.dat" );
        assertStrEquals( L"ABC.dat", PRIVATE_METHOD( SceneImp, filename_ )( scene ) );
        assertStrEquals( L"c:\\dir1/dir2", PRIVATE_METHOD( SceneImp, pathname_ )( scene ) );
    }

    [TestMethod]
    void SetColladaFactory() {
        ColladaFactoryPtr factory = ColladaFactoryPtr( new ColladaFactoryImp() );
        scene->setColladaFactoryBeforeLoad( &*factory );
        assertTrue( &*factory == PRIVATE_METHOD( SceneImp, colladaFactory_ )( scene ) );
    }

    [TestMethod]
    void SetRenderFactory() {
        RenderBufferFactoryNull nullRenderFactory;
        scene->setRenderFactory( &nullRenderFactory );
        assertTrue( &nullRenderFactory == PRIVATE_METHOD( SceneImp, renderFactory_ )( scene ) );
    }

    [TestMethod]
    void Display() {
        DummyNode_forDisplayTest sceneNode;
        PRIVATE_METHOD( SceneImp, currentScene_ )( scene ) = & sceneNode;
        scene->display( NULL );
        assertEquals( 1u, sceneNode.counter_ );
    }

    [TestMethod]
    void GetVisualScenePointers() {
        assertTrue( scene->load( getFilename() ) );
        assertTrue( PRIVATE_METHOD( SceneImp, currentScene_ )( scene ) == scene->getVisualScene( L"RootNode" ) );
        assertNotNull( scene->getNode( L"Sphere01" ) );
        assertNotNull( scene->getNode( L"Box01" ) );
        assertTrue( scene->getNode( L"Sphere01" ) != scene->getNode( L"Box01" ) );

        assertNull( scene->getNode( L"Nothing" ) );
        assertNull( scene->getVisualScene( L"Nothing" ) );
    }

    [TestMethod]
    void GetGeometry1() {
        assertTrue( scene->load( getFilename() ) );
        assertNull( scene->getGeometryByID( L"RootNode" ) );
        assertNull( scene->getGeometryByName( L"RootNode" ) );
        
        assertNotNull( scene->getGeometryByID( L"Sphere01-lib" ) );
        assertNotNull( scene->getGeometryByName( L"Sphere01Mesh" ) );
        assertTrue( scene->getGeometryByID( L"Sphere01-lib" ) ==  scene->getGeometryByName( L"Sphere01Mesh" ) );

        assertNotNull( scene->getGeometryByID( L"Box01-lib" ) );
        assertNotNull( scene->getGeometryByName( L"Box01Mesh" ) );
        assertTrue( scene->getGeometryByID( L"Box01-lib" ) ==  scene->getGeometryByName( L"Box01Mesh" ) );
    }

    [TestMethod]
    void GetGeometry2() {
        assertNull( scene->getGeometryByID( L"Sphere01Mesh" ) );
        assertNull( scene->getGeometryByName( L"Sphere01-lib" ) );
    }

    [TestMethod]
    void NullObjects() {
        assertNotNull( PRIVATE_METHOD( SceneImp, colladaFactory_ )( scene ) );
        assertNotNull( PRIVATE_METHOD( SceneImp, renderFactory_ )( scene ) );
        assertNotNull( PRIVATE_METHOD( SceneImp, dae_ )( scene ) );
        assertNotNull( PRIVATE_METHOD( SceneImp, currentScene_ )( scene ) );

        assertNull( PRIVATE_METHOD( SceneImp, collada_ )( scene ) );
        assertNull( PRIVATE_METHOD( SceneImp, currentCamera_ )( scene ) );
    }

};
