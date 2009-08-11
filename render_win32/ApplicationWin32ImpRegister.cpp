#include "my_render_win32_imp.h"
namespace my_render_win32_imp {

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM ApplicationWin32Imp::MyRegisterClass(HINSTANCE hInstance)
{
    HICON hIcon = NULL;

    WCHAR szExePath[MAX_PATH];
    GetModuleFileName( NULL, szExePath, MAX_PATH );
    if( hIcon == NULL ) // If the icon is NULL, then use the first one found in the exe
        hIcon = ExtractIcon( hInstance, szExePath, 0 );

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_DBLCLKS;
    wcex.lpfnWndProc    = ApplicationWin32Imp::MsgProc;
    wcex.cbClsExtra		= 0;
    wcex.cbWndExtra		= 0;
    wcex.hInstance		= hInstance;
    wcex.hIcon          = hIcon;
    wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = ( HBRUSH )GetStockObject( BLACK_BRUSH );
    wcex.lpszMenuName	= NULL;
    wcex.lpszClassName	= getRegisterClassName();
    wcex.hIconSm		= NULL;

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
HWND ApplicationWin32Imp::InitInstance(HINSTANCE hInstance, int nCmdShow, 
                                       const wchar_t * szTitle, int x, int y, int width, int height)
{
    HMENU hMenu = NULL;

    RECT rc;
    SetRect( &rc, 0, 0, width, height );
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, ( hMenu != NULL ) );

    HWND hWnd = CreateWindow(getRegisterClassName(), szTitle, WS_OVERLAPPEDWINDOW,
        x, y, width, height, NULL, NULL, hInstance, NULL);

    if (!hWnd)
        return NULL;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return hWnd;
}

void ApplicationWin32Imp::mainLoop() {
    //DXUTMainLoop(); // Enter into the DXUT render loop

    hAccelTable_ = NULL; // LoadAccelerators(hInstance_, MAKEINTRESOURCE(IDC_EMPTYWIN32));

    MSG msg;
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );

    while( WM_QUIT != msg.message )
    {
        // Use PeekMessage() so we can use idle time to render the scene. 
        const bool bGotMsg = ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 );

        if( bGotMsg )
            handleMessage( msg );
        else 
            actualRender_->render();
    }
}

inline void ApplicationWin32Imp::handleMessage( MSG & msg ) {
    // Translate and dispatch the message
    if (!TranslateAccelerator( msg.hwnd, NULL, &msg ))
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
}


}
