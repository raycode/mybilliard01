#pragma once


class RenderEventListenerImp : IMPLEMENTS_( RenderEventListener ) {
public: // from RenderEventListener
    virtual void display( Render * render );
    virtual void displayChanged( Render * render, bool modeChanged, bool deviceChanged);
    virtual void init( Render * render );
    virtual void reshape( Render * redner, int x, int y, int width, int height );

public:
    RenderEventListenerImp();

public:
    CModelViewerCamera          g_Camera;               // A model viewing camera
    CDXUTDialogResourceManager  g_DialogResourceManager; // manager for shared resources of dialogs
    CD3DSettingsDlg             g_SettingsDlg;          // Device settings dialog
    CDXUTTextHelper*            g_pTxtHelper;
    CDXUTDialog                 g_HUD;                  // dialog for standard controls
    CDXUTDialog                 g_SampleUI;             // dialog for sample specific controls

public: // Direct3D 9 resources
    ID3DXFont*                  g_pFont9;
    ID3DXSprite*                g_pSprite9;
    ID3DXEffect*                g_pEffect9;
};


