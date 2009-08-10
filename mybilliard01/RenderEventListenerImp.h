#pragma once


class RenderEventListenerImp : IMPLEMENTS_( RenderEventListener ) {
public: // from RenderEventListener
    virtual void init( Render * render );
    virtual void displayReset( Render * render, int x, int y, int width, int height );
    virtual void update( float elapsedTime );
    virtual void display( Render * render );
    virtual void displayLost( Render * render );
    virtual void destroy( Render * render );

public:
    RenderEventListenerImp();

private: // DXUT
    void initDXUT( Render * render );
    void displayResetDXUT( Render * render, int width, int height );
    void displayDXUT();
    void displayDXUTText();
    void displayLostDXUT();
    void destroyDXUT();

public:
    CModelViewerCamera          camera_;               // A model viewing camera
    CDXUTDialogResourceManager  dialogResourceManager_; // manager for shared resources of dialogs
    CD3DSettingsDlg             settingsDlg_;          // Device settings dialog
    CDXUTTextHelper*            textHelper_;
    CDXUTDialog                 hud_;                  // dialog for standard controls
    CDXUTDialog                 sampleUI_;             // dialog for sample specific controls

private: // Direct3D 9 resources
    ID3DXFont*                  font9_;
    ID3DXSprite*                sprite9_;
    ID3DXEffect*                effect9_;

private: // Collada scene object
    ScenePtr scene_;

private: // static
    static void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext );

};


