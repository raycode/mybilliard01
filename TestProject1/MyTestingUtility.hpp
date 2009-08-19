#define NOMINMAX
#include <windows.h>
#include <vcclr.h>
#include <string>
#include <iostream>
#include <fstream>
#include "../core_billiard/MyUtilities.h"


using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace MyTestingUtility
{
    using namespace std;
    using namespace my_utility;

    inline void setCurrentDirectory( TestContext^ testContext ) {
        pin_ptr< const wchar_t > deploymentDir = PtrToStringChars( testContext->TestDeploymentDir );
        ::SetCurrentDirectory( deploymentDir );
    }

    inline wstring getDeployedFilename( wstring filename ) {
        const size_t dirPos = filename.find_last_of( '\\' );
        const wstring filenameOnly = filename.c_str() + ( ( dirPos == wstring::npos ) ? 0 : ( dirPos + 1 ) );
        const wstring deployedFilename = filenameOnly;
        return deployedFilename;
    }

    inline bool isFileExist( wstring filename ) {
        std::ifstream ifs1( filename.c_str(), std::ios_base::binary );
        return ifs1.good();
    }

    inline String^ getString( wstring str ) {
        return gcnew String( str.c_str() );
    }

    inline String^ getString( string str ) {
        wstring  wcStr = convertString< wstring >( str );
        return gcnew String( wcStr.c_str() );
    }
}


#define assertTrue( obj ) { Assert::IsTrue( obj ); }
#define assertFalse( obj ) { Assert::IsFalse( obj ); }
#define assertEquals( expect, actual ) { Assert::AreEqual( expect, actual ); }
#define assertStrEquals( expect, actual ) { Assert::AreEqual( getString( expect ), getString( actual ) ); }
#define assertFloatEquals( expect, actual, delta ) { Assert::AreEqual( expect, actual, delta ); }
#define assertNull( obj ) { Assert::IsTrue( NULL == obj ); }
#define assertNotNull( obj ) { Assert::IsTrue( NULL != obj ); }
#define fail { Assert::Fail(); }


#define PRIVATE_METHOD( CLASS_NAME, methodName ) CLASS_NAME::TestingBackdoor::methodName
//#define PRIVATE_MEMBER( CLASS_NAME, methodName ) CLASS_NAME::TestingBackdoor::methodName

#define PRIVATE_METHOD_0( returnType, CLASS_NAME, methodName ) static returnType methodName( CLASS_NAME * obj ) { return obj->methodName(); }
#define PRIVATE_METHOD_1( returnType, CLASS_NAME, methodName, arg0 ) static returnType methodName( CLASS_NAME * obj, arg0 a0 ) { return obj->methodName( a0 ); }
#define PRIVATE_METHOD_2( returnType, CLASS_NAME, methodName, arg0, arg1 ) static returnType methodName( CLASS_NAME * obj, arg0 a0, arg1 a1 ) { return obj->methodName( a0, a1 ); }
#define PRIVATE_METHOD_3( returnType, CLASS_NAME, methodName, arg0, arg1, arg2 ) static returnType methodName( CLASS_NAME * obj, arg0 a0, arg1 a1, arg2 a2 ) { return obj->methodName( a0, a1, a2 ); }
#define PRIVATE_METHOD_4( returnType, CLASS_NAME, methodName, arg0, arg1, arg2, arg3 ) static returnType methodName( CLASS_NAME * obj, arg0 a0, arg1 a1, arg2 a2, arg3 a3 ) { return obj->methodName( a0, a1, a2, a3 ); }

#define PRIVATE_METHOD_0_VOID( CLASS_NAME, methodName ) static void methodName( CLASS_NAME * obj ) { obj->methodName(); }
#define PRIVATE_METHOD_1_VOID( CLASS_NAME, methodName, arg0 ) static void methodName( CLASS_NAME * obj, arg0 a0 ) { obj->methodName( a0 ); } 
#define PRIVATE_METHOD_2_VOID( CLASS_NAME, methodName, arg0, arg1 ) static void methodName( CLASS_NAME * obj, arg0 a0, arg1 a1 ) { obj->methodName( a0, a1 ); } 
#define PRIVATE_METHOD_3_VOID( CLASS_NAME, methodName, arg0, arg1, arg2 ) static void methodName( CLASS_NAME * obj, arg0 a0, arg1 a1, arg2 a2 ) { obj->methodName( a0, a1, a2 ); } 
#define PRIVATE_METHOD_4_VOID( CLASS_NAME, methodName, arg0, arg1, arg2, arg3 ) static void methodName( CLASS_NAME * obj, arg0 a0, arg1 a1, arg2 a2, arg3 a3 ) { obj->methodName( a0, a1, a2, a3 ); } 

#define PRIVATE_MEMBER( memberType, CLASS_NAME, memberName ) static memberType & memberName( CLASS_NAME * obj ) { return obj->memberName; }
