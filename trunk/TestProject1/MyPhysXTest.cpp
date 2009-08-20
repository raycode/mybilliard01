#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

//namespace TestProject1
//{
class MyUserNotify: public NXU_userNotify
{
public:
    virtual void NXU_errorMessage(bool isError, const char *str) {
        throw exception();
    }
} userNotify;


[TestClass]
public ref class MyPhysXTest
{
private:
    static TestContext^ testContext_;

    static wstring getFilename() {
        return getDeployedFilename( L"asset\\1ball1box.physx.xml" );
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
    void CreateMyPhysX()
    {
        MyPhysX phys;
	};

    [TestMethod]
    void FindAssetFile() {
        const wstring filename = getFilename();
        assertTrue( isFileExist( filename ) );

        wchar_t LoadFilename[512];
        wchar_t * const found = FindMediaFile( filename.c_str(), LoadFilename );

        assertTrue( NULL != found );
        assertTrue( isFileExist( found ) );
    }

    [TestMethod]
    void LoadColladaFile()
    {
        const wstring filename = getFilename();

        MyPhysX phys;
        const bool bLoad = phys.loadXMLFile( filename );
        assertTrue( bLoad );
        assertEquals( 2u, phys.getNumberOfActors() );
    }

    [TestMethod]
    void CheckActorNames()
    {
        MyPhysX phys;
        phys.loadXMLFile( getFilename() );

        array< String^ >^ namesOfActors = { L"Sphere01", L"Box01" };
        for( size_t i = 0; i < (size_t) namesOfActors->Length; ++i )
        {
            NxActor * const actor = phys.getActor( i );

            assertTrue( actor != NULL );
            assertEquals( namesOfActors[ i ], getString( actor->getName() ) );
        }
    }

    [TestMethod]
    void CheckSkinWidth()
    {
        MyPhysX phys;
        phys.loadXMLFile( getFilename() );

        for( size_t i = 0; i < (size_t) phys.getNumberOfActors(); ++i )
        {
            NxActor * const actor = phys.getActor( i );
            NxU32 nShapes = actor->getNbShapes();

            assertTrue( 1 <= nShapes );
            assertFloatEquals( 0.00025, (Double) actor->getShapes()[ 0 ]->getSkinWidth(), 0.00002 );
        }
    };
};

//}
