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
        return getDeployedFilename( L"asset\\1ball1box.dae" );
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
        Assert::IsTrue( isFileExist( filename ), getString( filename ) + " is not found." );
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

        const xsAnyURI url = instance_visual_scene->getUrl();
        Assert::AreEqual( "#RootNode", getString( url.originalStr() ) );
    }

    [TestMethod]
    void CheckInstanceVisualScene()
    {
        MyColladaLoader loader( getFilename() );

        domCOLLADA::domScene * const scene = loader.getCOLLADA()->getScene();
        domInstanceWithExtraRef instance_visual_scene = scene->getInstance_visual_scene();
        xsAnyURI url = instance_visual_scene->getUrl();

        domVisual_scene * const visual_scene = daeDowncast< domVisual_scene >( url.getElement() );
        Assert::IsTrue( NULL != visual_scene );
        Assert::AreEqual( "RootNode", getString( visual_scene->getName() ) );
    }

    [TestMethod]
    void CheckVisualScene()
    {
        wstring visualSceneId = L"RootNode";

        MyColladaLoader loader( getFilename() );

        domVisual_scene * const visual_scene = daeDowncast< domVisual_scene >( loader.idLookup( visualSceneId ) );
        Assert::IsTrue( NULL != visual_scene );
        Assert::AreEqual( getString( visualSceneId ), getString( visual_scene->getName() ) );

        Assert::AreEqual( 2u, visual_scene->getChildren().getCount() );
    }

    [TestMethod]
    void CheckVisualSceneNodes()
    {
        MyColladaLoader loader( getFilename() );

        wchar_t * const names[] = { L"Sphere01", L"Box01" };
        for( size_t i = 0; i < sizeof( names ) / sizeof( wchar_t* ); ++i ) {
            wchar_t * const name = names[ i ];

            domNode * const node = daeDowncast< domNode >( loader.idLookup( name ) );
            Assert::IsTrue( NULL != node );
            Assert::AreEqual( getString( name ), getString( node->getName() ) );
        }
    }

    [TestMethod]
    void CheckNodeTranslate()
    {
        MyColladaLoader loader( getFilename() );

        wchar_t * const names[] = { L"Sphere01", L"Box01" };
        float xAxies[] = { 0.f, 0.f };
        float yAxies[] = { 0.028f, -0.8f };
        float zAxies[] = { 0.f, 0.f };

        for( size_t i = 0; i < sizeof( names ) / sizeof( wchar_t* ); ++i ) {
            domNode * const node = daeDowncast< domNode >( loader.idLookup( names[ i ] ) );

            domTranslate_Array translates = node->getTranslate_array();
            Assert::AreEqual( 1u, translates.getCount() );

            domTranslate * const translate = translates[0];
            Assert::IsTrue( NULL != translate );

            const string transData = translate->getCharData();
            Assert::IsTrue( transData.size() > 1 );

            istringstream iss( transData );
            float x, y, z;
            iss >> x >> y >> z;
            Assert::AreEqual( xAxies[ i ], x, 0.001f );
            Assert::AreEqual( yAxies[ i ], y, 0.001f );
            Assert::AreEqual( zAxies[ i ], z, 0.001f );
        }
    }

    [TestMethod]
    void CheckGeometries()
    {
        MyColladaLoader loader( getFilename() );

        wchar_t * const names[] = { L"Sphere01", L"Box01" };

        for( size_t i = 0; i < sizeof( names ) / sizeof( wchar_t* ); ++i ) {
            domNode * const node = daeDowncast< domNode >( loader.idLookup( names[ i ] ) );

            domInstance_geometry_Array instance_geometries = node->getInstance_geometry_array();
            Assert::IsTrue( instance_geometries.getCount() >= 1 );

            domInstance_geometry * const instance_geometry = instance_geometries[0];
            Assert::IsTrue( NULL != instance_geometry );

            xsAnyURI url = instance_geometry->getUrl();
            domGeometry * const geometry = daeDowncast< domGeometry >( url.getElement() );
            Assert::IsTrue( NULL != geometry );

            domMeshRef mesh_ref = geometry->getMesh();
            Assert::IsTrue( NULL != mesh_ref );

            Assert::IsTrue( mesh_ref->getSource_array().getCount() >= 2 );
            Assert::IsTrue( NULL != mesh_ref->getVertices() );
        }
    }

    [TestMethod]
    void CheckGeometryMesh()
    {
        MyColladaLoader loader( getFilename() );

        wchar_t * const names[] = { L"Sphere01-lib", L"Box01-lib" };

        for( size_t i = 0; i < sizeof( names ) / sizeof( wchar_t* ); ++i ) {
            domGeometry * const geometry = daeDowncast< domGeometry >( loader.idLookup( names[ i ] ) );
            domMeshRef mesh_ref = geometry->getMesh();

            daeTArray<daeElementRef> children = mesh_ref->getChildren();
            const size_t nbSource = mesh_ref->getSource_array().getCount();
            const size_t offset = nbSource + 1 /* vertices element */ ;
            Assert::IsTrue( children.getCount() > offset );
            Assert::IsTrue( NULL != children[ offset ] );

            Assert::AreEqual( "polygons", getString( children[ offset ]->getElementName() ) );
        }
    }

    [TestMethod]
    void getInstancedVisualScene()
    {
        MyColladaLoader loader( getFilename() );

        domVisual_scene * const instanced_visual_scene = loader.getInstancedVisualScene();
        Assert::IsTrue( NULL != instanced_visual_scene );

        Assert::AreEqual( "RootNode", getString( instanced_visual_scene->getID() ) );
    }

    [TestMethod]
    void getMeshByNodeID()
    {
        MyColladaLoader loader( getFilename() );

        wchar_t * const nodeIDs[] = { L"Sphere01", L"Box01" };
        wchar_t * const geometryIDs[] = { L"Sphere01-lib", L"Box01-lib" };

        for( size_t i = 0; i < sizeof( nodeIDs ) / sizeof( wchar_t* ); ++i ) {

            vector< domMesh * > meshes = loader.getMeshByNodeID( nodeIDs[ i ] );

            Assert::AreEqual( 1u, meshes.size() );
            Assert::AreEqual( getString( geometryIDs[ i ] ) , getString( meshes[ 0 ]->getParentElement()->getID() ) );
        }
    }
};

//}
