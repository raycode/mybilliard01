#ifndef FSM_RenderListenerSMC_08_12_2009_15_53_11_H
#define FSM_RenderListenerSMC_08_12_2009_15_53_11_H
//----------------------------------------------
// RenderListenerSMC.h
// FSM:       RenderListenerSMC
// Context:   DummyEventListener_RenderWin32DX9Imp
// Version:   
// Generated: Wednesday 08/12/2009 at 15:53:11 EDT
//


// Included header files

#include "RenderListenerSMC.h"

namespace smc
{

// Forward Declarations

class RenderListenerSMC;

//----------------------------------------------
// RenderListenerSMCState: The base state class
//----------------------------------------------
class RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const = 0;
    virtual void resetSMC( RenderListenerSMC& );
    virtual void initSMC( RenderListenerSMC& );
    virtual void lostSMC( RenderListenerSMC& );
    virtual void displaySMC( RenderListenerSMC& );
    virtual void destroySMC( RenderListenerSMC& );
    virtual void updateSMC( RenderListenerSMC& );
};

//----------------------------------------------
// State: AfterInit
//----------------------------------------------
class RenderListenerSMCAfterInitState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterInit"; }
    virtual void resetSMC( RenderListenerSMC& );
};
//----------------------------------------------
// State: AfterReset
//----------------------------------------------
class RenderListenerSMCAfterResetState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterReset"; }
    virtual void displaySMC( RenderListenerSMC& );
    virtual void lostSMC( RenderListenerSMC& );
    virtual void updateSMC( RenderListenerSMC& );
};
//----------------------------------------------
// State: AfterLost
//----------------------------------------------
class RenderListenerSMCAfterLostState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterLost"; }
    virtual void destroySMC( RenderListenerSMC& );
    virtual void resetSMC( RenderListenerSMC& );
};
//----------------------------------------------
// State: AfterDestroy
//----------------------------------------------
class RenderListenerSMCAfterDestroyState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterDestroy"; }
};
//----------------------------------------------
// State: BeforeInit
//----------------------------------------------
class RenderListenerSMCBeforeInitState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "BeforeInit"; }
    virtual void initSMC( RenderListenerSMC& );
};
//----------------------------------------------
// RenderListenerSMC: The Finite State Machine class
//----------------------------------------------
class RenderListenerSMC: public DummyEventListener_RenderWin32DX9Imp
{
  public: 
    // Static State variables
    static RenderListenerSMCAfterInitState AfterInit;
    static RenderListenerSMCAfterResetState AfterReset;
    static RenderListenerSMCAfterLostState AfterLost;
    static RenderListenerSMCAfterDestroyState AfterDestroy;
    static RenderListenerSMCBeforeInitState BeforeInit;

    RenderListenerSMC(); // default Constructor

    // Event functions
    virtual void resetSMC() { itsState->resetSMC( *this ); }
    virtual void initSMC() { itsState->initSMC( *this ); }
    virtual void lostSMC() { itsState->lostSMC( *this ); }
    virtual void displaySMC() { itsState->displaySMC( *this ); }
    virtual void destroySMC() { itsState->destroySMC( *this ); }
    virtual void updateSMC() { itsState->updateSMC( *this ); }

    // State Accessor functions
    void SetState( RenderListenerSMCState& theState ) { itsState = &theState; }
    RenderListenerSMCState& GetState() const { return *itsState; }

    const char* GetCurrentStateName() const { return itsState->StateName(); }
    const char* GetVersion() const;

    virtual bool isStateCorrectToFinish() { return &BeforeInit == itsState || &AfterDestroy == itsState; }

  private: 
    RenderListenerSMCState* itsState;
};

}  // end namespace smc

#endif /* FSM_RenderListenerSMC_08_12_2009_15_53_11_H */
