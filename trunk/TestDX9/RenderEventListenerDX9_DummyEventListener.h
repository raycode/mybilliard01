#pragma once

class DummyEventListener_RenderWin32DX9Imp : public NullRenderEventListener {
public:
    DummyEventListener_RenderWin32DX9Imp()
        : lastErrorState_( NULL )
        , lastErrorTrans_( NULL )
    { }

    virtual void destroy() = 0;
    virtual void lost() = 0;
    virtual void reset() = 0;
    virtual void init() = 0;
    virtual bool isStateCorrectToFinish() = 0;

    virtual void init( Render * render ) {
        init();
    }

    virtual void displayReset( Render * render, int x, int y, int width, int height ) {
        reset();
    }

    virtual void displayLost( Render * render ) {
        lost();
    }

    virtual void destroy( Render * render ) {
        destroy();
    }

    virtual void update( float elapsedTime ) {
    }

    virtual void display( Render * render )
    {
    }

    void FSMError(const char* errorTrans, const char* lastState ) {
        lastErrorState_ = lastState;
        lastErrorTrans_ = errorTrans;
    }

    bool isStateCorrectSoFar() {
        return
            NULL == lastErrorState_ &&
            NULL == lastErrorTrans_ ;
    }

private:
    const char * lastErrorState_;
    const char * lastErrorTrans_;
};


