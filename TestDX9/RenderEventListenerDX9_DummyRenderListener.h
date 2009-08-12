#pragma once

class DummyEventListener_RenderWin32DX9Imp : public NullRenderEventListener {
public: // checking state machine
    DummyEventListener_RenderWin32DX9Imp()
        : lastErrorState_( NULL )
        , lastErrorTrans_( NULL )
        , countInit_( 0 )
        , countReset_( 0 )
        , countUpdate_( 0 )
        , countDisplay_( 0 )
        , countLost_( 0 )
        , countDestroy_( 0 )
    { }

    virtual void destroySMC() = 0;
    virtual void lostSMC() = 0;
    virtual void resetSMC() = 0;
    virtual void initSMC() = 0;
    virtual void updateSMC() = 0;
    virtual void displaySMC() = 0;

    virtual bool isStateCorrectToFinish() = 0;

    virtual void init( Render * ) OVERRIDE { initSMC(); ++countInit_; }
    virtual void displayReset( Render *, int, int, int, int ) OVERRIDE { resetSMC(); ++countReset_; }
    virtual void display( Render * ) OVERRIDE { displaySMC(); ++countDisplay_; }
    virtual void update( float ) OVERRIDE { updateSMC(); ++countUpdate_; }
    virtual void displayLost( Render * ) OVERRIDE { lostSMC(); ++countLost_; }
    virtual void destroy( Render * ) OVERRIDE { destroySMC(); ++countDestroy_; }

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

public:
    int countInit_;
    int countReset_;
    int countUpdate_;
    int countDisplay_;
    int countLost_;
    int countDestroy_;
};

// Code generator for StateMachine is from Object Mentor:
// http://www.objectmentor.com/resources/downloads.html
//
//#include "stdafx.h"
//#include "RenderEventListenerDX9_DummyRenderListener.h"
//virtual bool isStateCorrectToFinish() { return &BeforeInit == itsState || &AfterDestroy == itsState; }

