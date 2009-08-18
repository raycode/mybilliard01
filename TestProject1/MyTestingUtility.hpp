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

