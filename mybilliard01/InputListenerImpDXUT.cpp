#include "StdAfx.h"
#include "my_app.h"


bool InputListenerImp::MsgProcDXUT( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
    bool bNoFurtherProcessing;

    // Pass messages to settings dialog if its active
    if( renderListener_->settingsDlg_.IsActive() )
    {
        renderListener_->settingsDlg_.MsgProc( hWnd, uMsg, wParam, lParam );
        return false;
    }

    // Give the dialogs a chance to handle the message first
    bNoFurtherProcessing = renderListener_->hud_.MsgProc( hWnd, uMsg, wParam, lParam );
    if( bNoFurtherProcessing )
        return false;
    bNoFurtherProcessing = renderListener_->sampleUI_.MsgProc( hWnd, uMsg, wParam, lParam );
    if( bNoFurtherProcessing )
        return false;

    // Pass all remaining windows messages to camera so it can respond to user input
    renderListener_->camera_.HandleMessages( hWnd, uMsg, wParam, lParam );

    return true;
}

