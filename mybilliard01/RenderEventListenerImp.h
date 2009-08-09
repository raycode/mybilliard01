#pragma once


class RenderEventListenerImp : IMPLEMENTS_( RenderEventListener ) {
public:
    virtual void display( Render * render );
    virtual void displayChanged( Render * render, bool modeChanged, bool deviceChanged);
    virtual void init( Render * render );
    virtual void reshape( Render * redner, int x, int y, int width, int height );

public:
    CD3DSettingsDlg             g_SettingsDlg;          // Device settings dialog

};


