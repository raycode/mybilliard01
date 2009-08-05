#include "stdafx.h"
#include "../core_billiard/MediaPath.h"
#include < vcclr.h >

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

	public: 
        [ClassInitialize()]
        static void MyClassInitialize(TestContext^ testContext)
        {
            testContext_ = testContext;
        };

        [TestInitialize()]
        void MyTestInitialize()
        {
            pin_ptr<const wchar_t> deploymentDir = PtrToStringChars( testContext_->TestDeploymentDir );
            ::SetCurrentDirectory( deploymentDir );
        };

        [TestMethod]
        void Constructor()
        {
            MyPhysX phys;
		};

        static wstring getDeployedFilename( wstring filename ) {
            const size_t dirPos = filename.find_last_of( '\\' );
            const wstring filenameOnly = filename.c_str() + ( ( dirPos == wstring::npos ) ? 0 : ( dirPos + 1 ) );
            const wstring deployedFilename = filenameOnly;
            return deployedFilename;
        }

        static bool isFileExist( wstring filename ) {
            std::ifstream ifs1( filename.c_str(), std::ios_base::binary );
            return ifs1.good();
        }

        [TestMethod]
        void FindAssetFile() {
            const wstring filename = getDeployedFilename( ConstString::colladaPhysXFilename() );
            Assert::IsTrue( isFileExist( filename ), gcnew String( filename.c_str() ) + " is not found." );

            wchar_t LoadFilename[512];
            wchar_t * const found = FindMediaFile( filename.c_str(), LoadFilename );

            Assert::IsTrue( NULL != found );
            Assert::IsTrue( isFileExist( found ), gcnew String( found ) + " is not found." );
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
                Assert::AreEqual( namesOfActors[ i ], gcnew String( actor->getName() ) );
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
