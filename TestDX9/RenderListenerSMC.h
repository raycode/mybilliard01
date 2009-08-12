#ifndef FSM_RenderListenerSMC_08_12_2009_14_56_11_H
#define FSM_RenderListenerSMC_08_12_2009_14_56_11_H
//----------------------------------------------
// RenderListenerSMC.h
// FSM:       RenderListenerSMC
// Context:   RenderListenerContext
// Version:   
// Generated: Wednesday 08/12/2009 at 14:56:11 EDT
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
    virtual void destroy( RenderListenerSMC& );
    virtual void lost( RenderListenerSMC& );
    virtual void reset( RenderListenerSMC& );
    virtual void init( RenderListenerSMC& );
};

//----------------------------------------------
// State: AfterInit
//----------------------------------------------
class RenderListenerSMCAfterInitState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterInit"; }
    virtual void reset( RenderListenerSMC& );
};
//----------------------------------------------
// State: AfterReset
//----------------------------------------------
class RenderListenerSMCAfterResetState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterReset"; }
    virtual void lost( RenderListenerSMC& );
};
//----------------------------------------------
// State: AfterLost
//----------------------------------------------
class RenderListenerSMCAfterLostState : public RenderListenerSMCState
{
  public: 
    virtual const char* StateName() const
        { return "AfterLost"; }
    virtual void reset( RenderListenerSMC& );
    virtual void destroy( RenderListenerSMC& );
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
    virtual void init( RenderListenerSMC& );
};
//----------------------------------------------
// RenderListenerSMC: The Finite State Machine class
//----------------------------------------------
class RenderListenerSMC : public DummyEventListener_RenderWin32DX9Imp
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
    virtual void destroy() { itsState->destroy( *this ); }
    virtual void lost() { itsState->lost( *this ); }
    virtual void reset() { itsState->reset( *this ); }
    virtual void init() { itsState->init( *this ); }

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

#endif /* FSM_RenderListenerSMC_08_12_2009_14_56_11_H */
