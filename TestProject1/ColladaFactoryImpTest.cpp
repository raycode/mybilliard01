#include "stdafx.h"
#include "test_collada.h"
#include "SceneImp_Backdoor.hpp"
#include "ColladaFactoryImp_Backdoor.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

[TestClass]
public ref class ColladaFactoryImpTest
{
private:
    static TestContext^ testContext_;
    SceneImp * scene;
    ColladaFactoryImp * colladaFactory;

public: 
    [ClassInitialize()]
    static void MyClassInitialize(TestContext^ testContext) {
        testContext_ = testContext;
    };

    static wstring getFilename() {
        return getDeployedFilename( L"asset\\1ball1box.dae" );
    }

    [TestInitialize()]
    void MyTestInitialize() {
        setCurrentDirectory( testContext_ );

        scene = new SceneImp();
        scene->load( getFilename() );
        colladaFactory = dynamic_cast< ColladaFactoryImp *> ( PRIVATE_METHOD( SceneImp, colladaFactory_ )( scene ) );
        assertNotNull( colladaFactory );
    };

    [TestCleanup()]
    void MyTestCleanup() {
        delete scene;
    };

public:
    [TestMethod]
	void ConstructColladaFactory()
	{}

    [TestMethod]
    void CreatingInstance() {
        const size_t sizeBefore = PRIVATE_METHOD( ColladaFactoryImp, instances_ )( colladaFactory ).size();
        Instance * const newInstance = colladaFactory->createInstance( L"SomeURL" );
        assertNotNull( newInstance );
        assertEquals( sizeBefore + 1, PRIVATE_METHOD( ColladaFactoryImp, instances_ )( colladaFactory ).size() );
        colladaFactory->destroyInstance( newInstance );
        assertEquals( sizeBefore, PRIVATE_METHOD( ColladaFactoryImp, instances_ )( colladaFactory ).size() );
    }

    [TestMethod]
    void ResolveInstance1() {
        assertNotNull( colladaFactory->resolveInstanceURL( L"Sphere01-lib" ) );
    }

    [TestMethod]
    void ResolveInstance2() {
        Instance * const newInstance = colladaFactory->createInstance( L"Sphere01-lib" );
        assertNotNull( newInstance );
        assertStrEquals( L"Sphere01-lib", newInstance->getURL() );
        assertNotNull( newInstance->getResolvedReference() );
        assertTrue( newInstance->getResolvedReference() == scene->getGeometryByID( L"Sphere01-lib" ) );
    }

    [TestMethod]
    void ResolveInstance_wrongURL1() {
        Instance * const newInstance = colladaFactory->createInstance( L"Sphere01-lib " );
        assertNotNull( newInstance );
        assertStrEquals( L"Sphere01-lib ", newInstance->getURL() );
        assertNull( newInstance->getResolvedReference() );
    }

    [TestMethod]
    void ResolveInstance_wrongURL2() {
        assertNull( colladaFactory->resolveInstanceURL( L"WrongURL" ) );
    }

    [TestMethod]
    void RefineURL() {
        assertStrEquals( L"", PRIVATE_METHOD( ColladaFactoryImp, refineURL )( colladaFactory, L"" ) );
        assertStrEquals( L"Sphere", PRIVATE_METHOD( ColladaFactoryImp, refineURL )( colladaFactory, L"#Sphere" ) );
    }

    [TestMethod]
    void InitMember() {
        assertNotNull( PRIVATE_METHOD( ColladaFactoryImp, nodeFactory_ )( colladaFactory ) );
        assertNotNull( PRIVATE_METHOD( ColladaFactoryImp, geometryFactory_ )( colladaFactory ) );
    }
};
