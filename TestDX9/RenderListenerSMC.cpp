#include "stdafx.h"
#include "RenderEventListenerDX9_DummyEventListener.h"

//----------------------------------------------
// RenderListenerSMC.cpp
// FSM:       RenderListenerSMC
// Context:   RenderListenerContext
// Version:   
// Generated: Wednesday 08/12/2009 at 14:56:11 EDT
//


static char _versID[]  = "";

#include "RenderListenerSMC.h"

namespace smc
{

//----------------------------------------------
// Definitions of static state objects

//----------------------------------------------
RenderListenerSMCAfterInitState RenderListenerSMC::AfterInit;
RenderListenerSMCAfterResetState RenderListenerSMC::AfterReset;
RenderListenerSMCAfterLostState RenderListenerSMC::AfterLost;
RenderListenerSMCAfterDestroyState RenderListenerSMC::AfterDestroy;
RenderListenerSMCBeforeInitState RenderListenerSMC::BeforeInit;

//----------------------------------------------
// Default Event Functions

//----------------------------------------------

void RenderListenerSMCState::destroy(RenderListenerSMC& s)
  { s.FSMError("destroy", s.GetState().StateName()); }

void RenderListenerSMCState::lost(RenderListenerSMC& s)
  { s.FSMError("lost", s.GetState().StateName()); }

void RenderListenerSMCState::reset(RenderListenerSMC& s)
  { s.FSMError("reset", s.GetState().StateName()); }

void RenderListenerSMCState::init(RenderListenerSMC& s)
  { s.FSMError("init", s.GetState().StateName()); }

//----------------------------------------------
// The States and their Transitions
//----------------------------------------------

//----------------------------------------------
// AfterInit Actions and Transitions
//----------------------------------------------

// Starting State: AfterInit
// Event:          reset
//
void RenderListenerSMCAfterInitState::reset( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterReset);
}

//----------------------------------------------
// AfterReset Actions and Transitions
//----------------------------------------------

// Starting State: AfterReset
// Event:          lost
//
void RenderListenerSMCAfterResetState::lost( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterLost);
}

//----------------------------------------------
// AfterLost Actions and Transitions
//----------------------------------------------

// Starting State: AfterLost
// Event:          reset
//
void RenderListenerSMCAfterLostState::reset( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterReset);
}

// Starting State: AfterLost
// Event:          destroy
//
void RenderListenerSMCAfterLostState::destroy( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterDestroy);
}

//----------------------------------------------
// AfterDestroy Actions and Transitions
//----------------------------------------------

//----------------------------------------------
// BeforeInit Actions and Transitions
//----------------------------------------------

// Starting State: BeforeInit
// Event:          init
//
void RenderListenerSMCBeforeInitState::init( RenderListenerSMC& s )
{

    // Change the state
    s.SetState(RenderListenerSMC::AfterInit);
}

//----------------------------------------------
// State Machine Constructor: RenderListenerSMC
//  set Initial State to: BeforeInit
//
//----------------------------------------------
RenderListenerSMC::RenderListenerSMC() : itsState(&BeforeInit)
{
    // Entry functions for: BeforeInit
}

//  Get version information
//
const char* RenderListenerSMC::GetVersion() const
{ return _versID; }

}  // end namespace smc

