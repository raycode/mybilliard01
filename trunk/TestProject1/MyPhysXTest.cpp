#include "stdafx.h"
#include "MyTestingUtility.hpp"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace MyTestingUtility;

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
        const wstring filename = getDeployedFilename( ConstString::colladaPhysXFilename() );
        Assert::IsTrue( isFileExist( filename ), getString( filename ) + " is not found." );

        wchar_t LoadFilename[512];
        wchar_t * const found = FindMediaFile( filename.c_str(), LoadFilename );

        Assert::IsTrue( NULL != found );
        Assert::IsTrue( isFileExist( found ), getString( found ) + " is not found." );
    }

    [TestMethod]
    void LoadColladaFile()
    {
        const wstring filename = getDeployedFilename( ConstString::colladaPhysXFilename() );

        MyPhysX phys;
        const bool bLoad = phys.loadColladaFile( filename, &userNotify );
        Assert::IsTrue( bLoad );
        Assert::AreEqual( 2u, phys.countActors() );
    }

    [TestMethod]
    void CheckActorNames()
    {
        MyPhysX phys;
        phys.loadColladaFile( getDeployedFilename( ConstString::colladaPhysXFilename() ) );

        array< String^ >^ namesOfActors = { L"Sphere01", L"Box01" };
        for( size_t i = 0; i < (size_t) namesOfActors->Length; ++i )
        {
            NxActor * const actor = phys.getActor( i );

            Assert::IsTrue( actor != NULL );
            Assert::AreEqual( namesOfActors[ i ], getString( actor->getName() ) );
        }
    }

    [TestMethod]
    void CheckSkinWidth()
    {
        MyPhysX phys;
        phys.loadColladaFile( getDeployedFilename( ConstString::colladaPhysXFilename() ) );

        for( size_t i = 0; i < (size_t) phys.countActors(); ++i )
        {
            NxActor * const actor = phys.getActor( i );
            NxU32 nShapes = actor->getNbShapes();

            Assert::IsTrue( 1 <= nShapes );
            Assert::AreEqual( 0.00025, (Double) actor->getShapes()[ 0 ]->getSkinWidth(), 0.00002 );
        }
    };
};

//}
