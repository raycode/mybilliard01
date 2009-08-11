#include "DXUT.h"
#include "my_render_d3d9_imp.h"
namespace my_render_d3d9_imp {

#define MY_RENDER_MIN_WINDOW_SIZE_X 200
#define MY_RENDER_MIN_WINDOW_SIZE_Y 200


//--------------------------------------------------------------------------------------
// Handle messages to the application
//--------------------------------------------------------------------------------------
LRESULT CALLBACK ApplicationWin32Imp::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool    bKeys[256];                                // array of key state
    static bool    bMouseButtons[5];                          // array of mouse states

    // Consolidate the keyboard messages and pass them to the app's keyboard callback
    if( uMsg == WM_KEYDOWN ||
       uMsg == WM_SYSKEYDOWN ||
       uMsg == WM_KEYUP ||
       uMsg == WM_SYSKEYUP )
    {
        bool bKeyDown = ( uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN );
        DWORD dwMask = ( 1 << 29 );
        bool bAltDown = ( ( lParam & dwMask ) != 0 );

        bKeys[ ( BYTE )( wParam & 0xFF ) ] = bKeyDown;

        if( bKeyDown )
            g_app_->keyboardListener_->keyDown( ( UINT )wParam, bAltDown );
        else
            g_app_->keyboardListener_->keyUp( ( UINT )wParam, bAltDown );
    }

    // Consolidate the mouse button messages and pass them to the app's mouse callback
    if( uMsg == WM_LBUTTONDOWN ||
       uMsg == WM_LBUTTONUP ||
       uMsg == WM_LBUTTONDBLCLK ||
       uMsg == WM_MBUTTONDOWN ||
       uMsg == WM_MBUTTONUP ||
       uMsg == WM_MBUTTONDBLCLK ||
       uMsg == WM_RBUTTONDOWN ||
       uMsg == WM_RBUTTONUP ||
       uMsg == WM_RBUTTONDBLCLK ||
       uMsg == WM_XBUTTONDOWN ||
       uMsg == WM_XBUTTONUP ||
       uMsg == WM_XBUTTONDBLCLK ||
       uMsg == WM_MOUSEWHEEL ||
       uMsg == WM_MOUSEMOVE )
    {
        int xPos = ( short )LOWORD( lParam );
        int yPos = ( short )HIWORD( lParam );

        if( uMsg == WM_MOUSEWHEEL )
        {
            // WM_MOUSEWHEEL passes screen mouse coords
            // so convert them to client coords
            POINT pt;
            pt.x = xPos; pt.y = yPos;
            ScreenToClient( hWnd, &pt );
            xPos = pt.x; yPos = pt.y;
        }

        int nMouseWheelDelta = 0;
        if( uMsg == WM_MOUSEWHEEL )
            nMouseWheelDelta = ( short )HIWORD( wParam );

        const int nMouseButtonState = LOWORD( wParam );
        const bool bLeftButton = ( ( nMouseButtonState & MK_LBUTTON ) != 0 );
        const bool bRightButton = ( ( nMouseButtonState & MK_RBUTTON ) != 0 );
        const bool bMiddleButton = ( ( nMouseButtonState & MK_MBUTTON ) != 0 );
        const bool bSideButton1 = ( ( nMouseButtonState & MK_XBUTTON1 ) != 0 );
        const bool bSideButton2 = ( ( nMouseButtonState & MK_XBUTTON2 ) != 0 );

        bMouseButtons[0] = bLeftButton;
        bMouseButtons[1] = bMiddleButton;
        bMouseButtons[2] = bRightButton;
        bMouseButtons[3] = bSideButton1;
        bMouseButtons[4] = bSideButton2;

        g_app_->mouseListener_->onMouseEvent( xPos, yPos, bLeftButton, bRightButton, bMiddleButton, bSideButton1, bSideButton2, nMouseWheelDelta );
    }


    // Pass all messages to the app's MsgProc callback, and don't 
    // process further messages if the apps says not to.
    const bool bProceedMore = g_app_->win32MessageListener_->MsgProc( hWnd, uMsg, wParam, lParam );
    if( false == bProceedMore )
        return 0;


    switch( uMsg )
    {
    case WM_PAINT:
        break;

    case WM_SIZE:
        if( SIZE_MINIMIZED == wParam ) {
            g_app_->setMinimized( true );
            g_app_->setMaximized( false );
        }
        else
        {
            RECT rcCurrentClient;
            GetClientRect( DXUTGetHWND(), &rcCurrentClient );
            if( rcCurrentClient.top == 0 && rcCurrentClient.bottom == 0 )
            {
                // Rapidly clicking the task bar to minimize and restore a window
                // can cause a WM_SIZE message with SIZE_RESTORED when 
                // the window has actually become minimized due to rapid change
                // so just ignore this message
            }
            else if( SIZE_MAXIMIZED == wParam )
            {
                g_app_->setMinimized( false );
                g_app_->setMaximized( true );
                g_app_->render_->force_displayReset();
            }
            else if( SIZE_RESTORED == wParam )
            {
                //DXUTCheckForDXGIFullScreenSwitch();
                if( g_app_->isMaximized() )
                {
                    g_app_->setMaximized( false );
                    g_app_->render_->force_displayReset();
                }
                else if( g_app_->isMinimized() )
                {
                    g_app_->setMinimized( false );
                    g_app_->render_->force_displayReset();
                }
                else if( g_app_->isSizeInMove() )
                {
                    // If we're neither maximized nor minimized, the window size 
                    // is changing by the user dragging the window edges.  In this 
                    // case, we don't reset the device yet -- we wait until the 
                    // user stops dragging, and a WM_EXITSIZEMOVE message comes.
                }
                else
                {
                    // This WM_SIZE come from resizing the window via an API like SetWindowPos() so 
                    // resize and reset the device now.
                    g_app_->render_->force_displayReset();
                }
            }
        }
        break;

    case WM_GETMINMAXINFO:
        ( ( MINMAXINFO* )lParam )->ptMinTrackSize.x = MY_RENDER_MIN_WINDOW_SIZE_X;
        ( ( MINMAXINFO* )lParam )->ptMinTrackSize.y = MY_RENDER_MIN_WINDOW_SIZE_Y;
        break;

    case WM_ENTERSIZEMOVE:
        // Halt frame movement while the app is sizing or moving
        g_app_->setSizeInMove( true );
        break;

    case WM_EXITSIZEMOVE:
        g_app_->render_->force_displayReset();
        g_app_->setSizeInMove( false );
        break;

    case WM_MOUSEMOVE:
        if( false == g_app_->isWindowedMode() )
        {
            POINT ptCursor;
            GetCursorPos( &ptCursor );
            g_app_->render_->setCursorPosition( ptCursor.x, ptCursor.y );
        }
        break;

    case WM_SETCURSOR:
        if( false == g_app_->isWindowedMode() )
        {
            g_app_->render_->showCursor( true );
            return true; // prevent Windows from setting cursor to window class cursor
        }
        break;

    case WM_ACTIVATEAPP:
            // Enable controller rumble & input when activating app
            DXUTEnableXInput( true );
        break;

    case WM_ENTERMENULOOP:
        // Pause the app when menus are displayed
        break;

    case WM_EXITMENULOOP:
        break;

    case WM_MENUCHAR:
        // A menu is active and the user presses a key that does not correspond to any mnemonic or accelerator key
        // So just ignore and don't beep
        return MAKELRESULT( 0, MNC_CLOSE );
        break;

    case WM_NCHITTEST:
        // Prevent the user from selecting the menu in full screen mode
        if( !g_app_->isWindowedMode() )
            return HTCLIENT;
        break;

    case WM_POWERBROADCAST:
        switch( wParam )
        {
#ifndef PBT_APMQUERYSUSPEND
#define PBT_APMQUERYSUSPEND 0x0000
#endif
        case PBT_APMQUERYSUSPEND:
            // At this point, the app should save any data for open
            // network connections, files, etc., and prepare to go into
            // a suspended mode.  The app can use the MsgProc callback
            // to handle this if desired.
            return true;

#ifndef PBT_APMRESUMESUSPEND
#define PBT_APMRESUMESUSPEND 0x0007
#endif
        case PBT_APMRESUMESUSPEND:
            // At this point, the app should recover any data, network
            // connections, files, etc., and resume running from when
            // the app was suspended. The app can use the MsgProc callback
            // to handle this if desired.

            // QPC may lose consistency when suspending, so reset the timer
            // upon resume.
            //DXUTGetGlobalTimer()->Reset();
            return true;
        }
        break;

    case WM_SYSCOMMAND:
        // Prevent moving/sizing in full screen mode
        switch( ( wParam & 0xFFF0 ) )
        {
        case SC_MOVE:
        case SC_SIZE:
        case SC_MAXIMIZE:
        case SC_KEYMENU:
            if( ! g_app_->isWindowedMode() )
                return 0;
            break;
        }
        break;

    case WM_SYSKEYDOWN:
        {
            switch( wParam )
            {
            case VK_RETURN:
                {
                    // Toggle full screen upon alt-enter 
                    DWORD dwMask = ( 1 << 29 );
                    if( ( lParam & dwMask ) != 0 ) // Alt is down also
                    {
                        // Toggle the full screen/window mode
                        g_app_->render_->toggleFullScreen();
                        return 0;
                    }
                }
            }
            break;
        }

    case WM_KEYDOWN:
        {
            switch( wParam )
            {
            case VK_ESCAPE:
                {
                    SendMessage( hWnd, WM_CLOSE, 0, 0 );
                    break;
                }

            case VK_PAUSE:
                break;
            }
        }
        break;

    case WM_CLOSE:
        {
            HMENU hMenu;
            hMenu = GetMenu( hWnd );
            if( hMenu != NULL )
                DestroyMenu( hMenu );
            DestroyWindow( hWnd );
            UnregisterClass( getRegisterClassName(), NULL );
            //g_app_->SetHWNDFocus( NULL );
            //g_app_->SetHWNDDeviceFullScreen( NULL );
            //g_app_->SetHWNDDeviceWindowed( NULL );
            return 0;
        }

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    // Don't allow the F10 key to act as a shortcut to the menu bar
    // by not passing these messages to the DefWindowProc only when
    // there's no menu present
    if( ( uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP ) && ( wParam == VK_F10 ) )
       return 0;

    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}


}
