#define _CRT_SECURE_NO_WARNINGS
#include "my_render_win32_imp.h"
namespace my_render_win32_imp {


bool FileSystemHelper::isFileExist( wstring filename )
{
    FILE * const fileHandle = fopen( convertString( filename ).c_str(), "r" );
    return NULL != fileHandle;
}

wstring FileSystemHelper::getFullPathnameWithoutFilename( wstring fullname ) {
    wchar_t newPathname[ MAX_PATH ];
    wchar_t * filePart;
    ::GetFullPathName( fullname.c_str(), MAX_PATH, newPathname, & filePart );
    if( NULL != filePart ) filePart[ 0 ] = NULL;
    return newPathname;
}

wstring FileSystemHelper::getFullname( wstring filename ) {
    wchar_t newPathname[ MAX_PATH ];
    ::GetFullPathName( filename.c_str(), MAX_PATH, newPathname, NULL );
    return newPathname;
}


}