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


    RenderEventListenerImp renderEvent;
    RenderErrorListenerImp renderError;

    RenderD3D9Imp render;
    render.addEventListener( &renderEvent );
    render.addErrorListener( &renderError );


    InputListenerImp inputListener( &renderEvent );

    ApplicationWin32Imp app;
    app.setRender( &render );
    app.addKeyboardListener( &inputListener );
    app.addMouseListener( &inputListener );
    app.setScreenWidth( 640 );
    app.setScreenHeight( 480 );
    app.setWindowedMode( true );
    app.setScreenTitle( ConstString::windowTitle() );
    app.openWindow();

    return 0;
}









