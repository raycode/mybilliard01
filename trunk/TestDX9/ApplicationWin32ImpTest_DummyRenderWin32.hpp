#pragma once

class DummyRenderWin32_ApplicationWin32Imp : public RenderWin32Null {
public:
    DummyRenderWin32_ApplicationWin32Imp()
        : renderCounter_(0)
    {}

    virtual void setHWND( HWND hWnd ) OVERRIDE {
        hWnd_ = hWnd;
    }

    virtual void renderOneFrame() OVERRIDE {
        ++renderCounter_;
        if( renderCounter_ <= 10 ) return;
        PostQuitMessage( 0 );
    }

    virtual bool createDevice( bool , int , int ) OVERRIDE { return true; }
    virtual bool isDeviceCreated()  OVERRIDE { return true; }

private:
    int renderCounter_;
    HWND hWnd_;
};

