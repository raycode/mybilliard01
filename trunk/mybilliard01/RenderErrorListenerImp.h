#pragma once


class RenderErrorListenerImp : IMPLEMENTS_( RenderErrorListener ) {
public:
    virtual void createWindow( wstring );
    virtual void createDevice( wstring );

};


