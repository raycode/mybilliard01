//--------------------------------------------------------------------------------------
// File: SimpleSample.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "StdAfx.h"
#include "my_app.h"



//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow )
{
    //_CrtSetBreakAlloc( 630935 );
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    SetDllDirectory( ConstString::dllDirectory().c_str() );

    ApplicationWin32 * const app = new ApplicationWin32Imp();
    {
        MyRenderEventListenerImp * renderEvent = new MyRenderEventListenerImp(
            L"..\\asset\\table.dae",
            L"..\\asset\\table.physx.xml"
        );

        MyInputListenerImp * inputListener = new MyInputListenerImp( renderEvent, app );


        Render * const render = new RenderWin32DX9Imp();
        render->addRenderEventListener( renderEvent );

        app->setRender( render );
        app->addKeyboardListener( inputListener );
        app->addMouseListener( inputListener );
        app->addWin32MessageListener( inputListener );
        app->setScreenWidth( 640 );
        app->setScreenHeight( 480 );
        app->setWindowedMode( true );
        app->setScreenTitle( ConstString::windowTitle() );
        app->start();

        delete render;
        delete inputListener;
        delete renderEvent;
    }
    delete app;

    return 0;
}









