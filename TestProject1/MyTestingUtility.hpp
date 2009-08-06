#include "stdafx.h"
#include "../core_billiard/MediaPath.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace MyTestingUtility
{

    static void setCurrentDirectory( TestContext^ testContext ) {
        pin_ptr< const wchar_t > deploymentDir = PtrToStringChars( testContext->TestDeploymentDir );
        ::SetCurrentDirectory( deploymentDir );
    }

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

    static String^ getString( wstring str ) {
        return gcnew String( str.c_str() );
    }

    static String^ getString( string str ) {
        return gcnew String( convertString< wstring >( str ).c_str() );
    }
}
