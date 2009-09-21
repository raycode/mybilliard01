#include <iostream>

#ifdef _WIN32
#pragma warning ( disable : 4127 4100 4512 )
#endif // _WIN32
#include "gtest/gtest.h"


#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <tchar.h>

const TCHAR * getCustomDllDirectory();

#endif // _WIN32


int main(int argc, char **argv)
{
#ifdef _WIN32
    //_CrtSetBreakAlloc( 630935 );
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif // DEBUG

#ifdef GTEST_CUSTOM_DLL_DIRECTORY
    SetDllDirectory( getCustomDllDirectory() );
#endif // GTEST_CUSTOM_DLL_DIRECTORY

#endif // _WIN32

    std::cout << "Running main() from my_gtest_main.cc\n";

    testing::InitGoogleTest(&argc, argv);
    const int rst = RUN_ALL_TESTS();

    getchar();
    return rst;
}


#ifdef _WIN32

void createCmdLine( LPTSTR lpCmdLine, int * argc, TCHAR *** argv );
void destroyCmdLine( TCHAR ** argv );


int APIENTRY wWinMain( HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    //_CrtSetBreakAlloc( 630935 );
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    OutputDebugStr( _TEXT( "Running wWinMain() from my_gtest_main.cc\n" ) );
#endif

#ifdef GTEST_CUSTOM_DLL_DIRECTORY
    SetDllDirectory( getCustomDllDirectory() );
#endif

    int     argc;
    TCHAR** argv;
    createCmdLine( lpCmdLine, &argc, &argv );

    testing::InitGoogleTest( &argc, argv );
    const int rst = RUN_ALL_TESTS();

    destroyCmdLine( argv );
    return rst;
}

void createCmdLine( LPTSTR lpCmdLine, int * argc, TCHAR *** argv )
{
    // count the arguments
    {
        *argc = 1;

        TCHAR * arg  = lpCmdLine;
         while (arg[0] != NULL)
         {
            ++(*argc);

            while (arg[0] != NULL && arg[0] != ' ')
                ++arg;
        }
    }

    // tokenize the arguments
    {
        *argv = (TCHAR**)malloc( (*argc) * sizeof(TCHAR*) );

        TCHAR * arg = lpCmdLine;
        for( int i = 1; i < *argc; ++i )
        {
            (*argv)[ i ] = arg;

            while (arg[0] != NULL && arg[0] != ' ')
                ++arg;

            arg[0] = NULL;    
            ++arg;
        }    
    }

    // put the program name into argv[0]
    TCHAR * const filename = (TCHAR*) malloc( _MAX_PATH * sizeof( TCHAR ) );

    GetModuleFileName( NULL, filename, _MAX_PATH );
    (*argv)[0] = filename;
}

void destroyCmdLine( TCHAR ** argv )
{
    free( argv[ 0 ] );
    free( argv );
}

#endif // _WIN32
