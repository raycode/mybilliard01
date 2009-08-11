//--------------------------------------------------------------------------------------
// File: SimpleSample.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "DXUT.h"
#include "my_app.h"



//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    SetDllDirectory( ConstString::dllDirectoryForColladaDOM().c_str() );

    //assert(
    //    ApplicationWin32Imp::MyRegisterClass( GetModuleHandle( NULL ) ) );

    //const int x = 0;
    //const int y = 0;
    //const int width = 640;
    //const int height = 480;
    //const wchar_t * title = L"AAA";
    //ApplicationWin32Imp::InitInstance( hInstance, SW_SHOW, title, x, y, width, height );

    //assert( render.createDevice( true, width, height ) );

    //MSG msg;
    //msg.message = WM_NULL;
    //PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

    //while( WM_QUIT != msg.message )
    //{
    //    // Use PeekMessage() so we can use idle time to render the scene. 
    //    const bool bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

    //    if( bGotMsg )
    //        ApplicationWin32Imp::handleMessage( msg );
    //}


    RenderEventListenerImp * renderEvent = new RenderEventListenerImp();
    RenderErrorListener * renderError = new RenderErrorListenerImp();

    RenderWin32DX9 * render = new RenderWin32DX9Imp();
    render->addEventListener( renderEvent );
    render->addErrorListener( renderError );


    InputListenerImp * inputListener = new InputListenerImp( renderEvent );

    ApplicationWin32 * app = new ApplicationWin32Imp();
    app->setRender( render );
    app->addKeyboardListener( inputListener );
    app->addMouseListener( inputListener );
    app->addWin32MessageListener( inputListener );
    app->setScreenWidth( 640 );
    app->setScreenHeight( 480 );
    app->setWindowedMode( true );
    app->setScreenTitle( ConstString::windowTitle() );
    app->start();

    delete app;
    delete inputListener;
    delete render;
    delete renderError;
    delete renderEvent;

    return 0;
}









